#include "GpsController.h"

GpsController::GpsController():
	position(Position(0, 0)),
	terminateSensorThread(false)
{
}

void GpsController::start()
{
	if (sensorThread) {
		return;
	}
	terminateSensorThread = false;
	sensorThread.reset(new std::thread([this] { this->runSensor(); }));
}

void GpsController::stop()
{
	if (!sensorThread) {
		return;
	}
	terminateSensorThread = true;
	sensorThread->join();
	sensorThread.reset();
}

Position GpsController::getPosition()
{
	return this->position;
}


void GpsController::runSensor()
{
	while (!terminateSensorThread) {
		this->sensor.measure();

		this->position = Position(this->sensor.longitude, this->sensor.latitude);

		usleep(1e6);
	}
}
