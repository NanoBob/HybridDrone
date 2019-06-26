#pragma once
#include "PwmController.h"
#include "Motor.h"

class MotorController
{
	int address;
	PwmController* pwm;

	void init();
	void arm();

	void stopAllMotors();
	void runAllMotors(double value);

	Motor* frontLeft;
	Motor* frontRight;
	Motor* rearLeft;
	Motor* rearRight;

	double yawPower;
	double pitchPower;
	double rollPower;
	double throttlePower;

	double limitThrust(double thrust, double limit);
	void updateMotors();
public:
	MotorController(int address = 0x40);
	~MotorController();

	void yaw(double value) { yawPower = limitThrust(value, 0.3); updateMotors(); }
	void pitch(double value) { pitchPower = limitThrust(value, 0.3); updateMotors(); }
	void roll(double value) { rollPower = limitThrust(value, 0.3); updateMotors(); }
	void throttle(double value) { throttlePower = limitThrust(value, 0.3); updateMotors(); }

	void shutdown();
};

