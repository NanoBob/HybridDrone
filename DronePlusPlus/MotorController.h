#pragma once

#include "PwmController.h"
#include "Motor.h"

#include <memory>

class MotorController
{
	int address;
	std::shared_ptr<PwmController> pwm;

	void arm();

	void stopAllMotors();
	void runAllMotors(double value);

	double yawPower;
	double pitchPower;
	double rollPower;
	double throttlePower;

	bool enabled;

	double limitThrust(double thrust, double limit);
public:
	MotorController(int address = 0x40);

	Motor frontLeft;
	Motor frontRight;
	Motor rearLeft;
	Motor rearRight;

	void yaw(double value) { yawPower = limitThrust(value, 0.3); }
	void pitch(double value) { pitchPower = limitThrust(value, 0.3); }
	void roll(double value) { rollPower = limitThrust(value, 0.3); }
	void throttle(double value) { throttlePower = limitThrust(value, 0.3); }
	void updateMotors();

	void test(double value);

	void shutdown();
	void disable();
	void enable();
};

