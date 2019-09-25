#include "MotorController.h"
#include <iostream>


MotorController::MotorController(int address) :
	yawPower(0),
	pitchPower(0),
	rollPower(0),
	throttlePower(0),
	enabled(true),
	initialized(false)
{
	pwm = new PwmController(address);

	init();
}

MotorController::~MotorController()
{
	delete this->pwm;
}

double MotorController::limitThrust(double thrust, double limit)
{
	if (thrust < 0) {
		return std::max(thrust, -limit);
	}
	return std::min(thrust, limit);
}

void MotorController::updateMotors()
{
	if (!enabled) {
		return;
	}

	frontLeft->run(throttlePower + pitchPower + rollPower + yawPower);
	frontRight->run(throttlePower + pitchPower - rollPower - yawPower);
	rearLeft->run(throttlePower - pitchPower + rollPower - yawPower);
	rearRight->run(throttlePower - pitchPower - rollPower + yawPower);
}

void MotorController::test(double value)
{
	for (float i = 0; i < value; i += value * .0004) {
		this->throttle(i);
		usleep(12500);
	}
	for (float i = value; i >= 0; i -= value * .0004) {
		this->throttle(i);
		usleep(12500);
	}
}

void MotorController::shutdown()
{
	stopAllMotors();
}

void MotorController::init()
{
	enabled = true;

	pwm->setDesiredFrequency(180);

	frontLeft = new Motor(*pwm, 0);
	frontRight = new Motor(*pwm, 4);
	rearRight = new Motor(*pwm, 8);
	rearLeft = new Motor(*pwm, 12);

	arm();
	initialized = true;
}

void MotorController::arm()
{
	stopAllMotors();
	usleep(4 * 1000 * 1000);

	this->runAllMotors(1);
	usleep(4 * 1000 * 1000);

	std::cout << "Running 0%\n";
	this->runAllMotors(0);
	usleep(4 * 1000 * 1000);

	std::cout << "Running 5%\n";
	this->runAllMotors(0.05);
	usleep(5 * 1000 * 1000);

	std::cout << "Arming finished\n";
	this->runAllMotors(0.0);
}

void MotorController::stopAllMotors()
{
	frontLeft->stop();
	frontRight->stop();
	rearRight->stop();
	rearLeft->stop();
}

void MotorController::runAllMotors(double value)
{
	if (! enabled) {
		return;
	}
	frontLeft->run(value);
	frontRight->run(value);
	rearRight->run(value);
	rearLeft->run(value);
}

void MotorController::disable()
{
	enabled = false;

	frontLeft->run(0);
	frontRight->run(0);
	rearRight->run(0);
	rearLeft->run(0);

	std::cout << "Disabled motors\n";
}

void MotorController::enable()
{
	enabled = true;
	std::cout << "Enabled motors\n";
}
