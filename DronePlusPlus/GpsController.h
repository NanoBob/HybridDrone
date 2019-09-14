#pragma once
#include "GpsSensor.h"
#include "Position.h"
class GpsController
{
private:
	GpsSensor sensor;

	Position position;

	bool terminateSensorThread;
	std::thread* sensorThread;

	void runSensor();
public:
	GpsController();

	void start();
	void stop();

	Position getPosition();
};

