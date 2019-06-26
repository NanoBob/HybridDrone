#include "Motor.h"
#include <iostream>


Motor::Motor(PwmController& pwm, int id) : pwm(pwm), id{ id }
{
}

Motor::~Motor()
{
}

void Motor::run(double speed)
{
	this->speed = speed;
	this->running = speed > 0;
	if (speed <= 0) {
		pwm.setPulseParameters(this->id, servoMin);
	}
	else {
		pwm.setPulseParameters(this->id, servoMin + speed * (servoMax - servoMin));
	}
}

void Motor::stop()
{
	pwm.setPulseParameters(this->id, 0);
}

double Motor::getSpeed()
{
	return this->speed;
}

bool Motor::isRunning()
{
	return this->running;
}
