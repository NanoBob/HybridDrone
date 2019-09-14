#pragma once

#include <memory>
#include "GpsSensor.h"
#include "Position.h"

class GpsController
{
private:
	GpsSensor sensor;

	Position position;

	bool terminateSensorThread;
	std::unique_ptr<std::thread> sensorThread;

	void runSensor();
public:
	GpsController();

	void start();
	void stop();

	Position getPosition();
};

