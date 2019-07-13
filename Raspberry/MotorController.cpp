#include "MotorController.h"
#include <iostream>


MotorController::MotorController(int address)
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
	return thrust > limit ? limit :
		thrust < -limit ? -limit :
		thrust;
}

void MotorController::updateMotors()
{
	frontLeft->run(throttlePower + pitchPower + rollPower + yawPower);
	frontRight->run(throttlePower + pitchPower - rollPower - yawPower);
	rearLeft->run(throttlePower - pitchPower + rollPower - yawPower);
	rearRight->run(throttlePower - pitchPower - rollPower + yawPower);
}

void MotorController::shutdown()
{
	frontLeft->stop();
	frontRight->stop();
	rearLeft->stop();
	rearRight->stop();
}

void MotorController::init()
{
	pwm->setDesiredFrequency(180);

	frontLeft = new Motor(*pwm, 0);
	frontRight = new Motor(*pwm, 4);
	rearRight = new Motor(*pwm, 8);
	rearLeft = new Motor(*pwm, 12);

	arm();
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
	frontLeft->run(value);
	frontRight->run(value);
	rearRight->run(value);
	rearLeft->run(value);
}
