#pragma once

#include "PwmController.h"

#include <memory>

class Motor
{
private:
	int servoMax = (int)(4000 * 0.4);
	int servoMin = (int)(4000 * 0.4 * 0.35);

	double speed;
	bool running;

	std::shared_ptr<PwmController> pwm;

public:
	int id;

	Motor(std::shared_ptr<PwmController> pwm, int id);
	~Motor();

	void run(double speed);
	void stop();

	double getSpeed();
	bool isRunning();
};

