#pragma once
#include "Orientation.h"
#include <thread>
#include "OrientationSensor.h"
#include "MotorController.h"
class OrientationController
{
private:

	OrientationSensor* sensor;
	MotorController& motors;

	Orientation orientation;
	Orientation targetOrientation;

	bool isRunning;
	bool terminateThread;
	std::thread* sensorThread;


	Orientation sanitizeOrientation(Orientation orientation);
	void run();
public:
	OrientationController(MotorController& motors);
	~OrientationController();

	void start();
	void stop();

	Orientation getOrientation();
	Orientation getTargetOrientation();
	void setTargetOrientation(Orientation orientation);

};
