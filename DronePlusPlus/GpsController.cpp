#include "GpsController.h"

GpsController::GpsController():
	position(Position(0, 0)),
	terminateSensorThread(false),
	sensorThread(nullptr)
{
	this->sensor = new GpsSensor();
}

void GpsController::start()
{
	if (sensorThread != nullptr) {
		return;
	}
	terminateSensorThread = false;
	sensorThread = new std::thread([this] { this->runSensor(); });
}

void GpsController::stop()
{
	if (sensorThread == nullptr) {
		return;
	}
	terminateSensorThread = true;
	sensorThread->join();
	delete sensorThread;
	sensorThread = nullptr;
}

Position GpsController::getPosition()
{
	return this->position;
}


void GpsController::runSensor()
{
	while (!terminateSensorThread) {
		this->sensor->measure();

		this->position = Position(this->sensor->longitude, this->sensor->latitude);

		usleep(1e6);
	}
}