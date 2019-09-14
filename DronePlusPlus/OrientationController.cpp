#include "OrientationController.h"

#include <iostream>
#include <unistd.h>

OrientationController::OrientationController(MotorController& motors) : 
	isRunning(false), 
	orientation(0, 0, 0), 
	targetOrientation(0, 0, 0), 
	terminateSensorThread(false), 
	motors(motors), 
	orientationAssistAgression(1.0f/45.0f), 
	readCount(0),
	sensorThread(nullptr),
	motorThread(nullptr)
{
	sensor = new OrientationSensor(0x28);
}

OrientationController::~OrientationController()
{
	terminateSensorThread = true;
	if (sensorThread != nullptr) {
		sensorThread->join();
		delete sensorThread;
	}

	delete sensor;
}

void OrientationController::start()
{
	if (sensorThread != nullptr) {
		return;
	}
	terminateSensorThread = false;
	isRunning = true;
	sensorThread = new std::thread([this] { this->runOrientation(); });

}

void OrientationController::stop()
{
	if (sensorThread == nullptr) {
		return;
	}
	isRunning = false;
	terminateSensorThread = true;
	sensorThread->join();
	delete sensorThread;
	sensorThread = nullptr;
}

void OrientationController::startOrientationAssist()
{
	if (motorThread != nullptr) {
		return;
	}
	terminateMotorThread = false;
	motorThread = new std::thread([this] { this->runMotors(); });
}

void OrientationController::stopOrientationAssit()
{
	if (motorThread == nullptr) {
		return;
	}
	terminateMotorThread = true;
	motorThread->join();
	delete motorThread;
	motorThread = nullptr;
}

Orientation OrientationController::getOrientation()
{
	return this->orientation;
}

Orientation OrientationController::getTargetOrientation()
{
	return this->targetOrientation;
}

void OrientationController::setTargetOrientation(Orientation orientation)
{
	this->orientation = orientation;
}

void OrientationController::setOrientationAssistAgression(float value)
{
	this->orientationAssistAgression = value;
}

Orientation OrientationController::sanitizeOrientation(Orientation orientation)
{
	if (orientation.yaw > 180) {
		orientation.yaw = orientation.yaw - 360;
	}
	if (orientation.pitch > 180) {
		orientation.pitch = orientation.pitch - 360;
	}
	if (orientation.roll > 180) {
		orientation.roll = orientation.roll - 360;
	}

	return orientation;
}

void OrientationController::runOrientation() {
	while (!terminateSensorThread) {
		Orientation orientation = sensor->getOrientation();

		this->orientation =  sanitizeOrientation(orientation);
		this->readCount = (this->readCount + 1) % 1024;

		usleep(10 * 1000);
	}
}

void OrientationController::runMotors()
{
	int currentReadCount = this->readCount;
	while (!terminateMotorThread) {
		while (this->readCount == currentReadCount) {
			usleep(100);
		}
		this->performStabilityAssist();
	}
}

void OrientationController::performStabilityAssist()
{
	Orientation orientation = this->orientation;
	Orientation targetOrientation = this->targetOrientation;

	//handleAxisOffset(Axis::Yaw, targetOrientation.yaw - orientation.yaw);
	handleAxisOffset(Axis::Pitch, targetOrientation.pitch - orientation.pitch);
	handleAxisOffset(Axis::Roll, targetOrientation.roll - orientation.roll);

	this->motors.updateMotors();
}

void OrientationController::handleAxisOffset(Axis axis, float offset)
{
	float targetPower = 0.1 * std::min(this->orientationAssistAgression * offset, 1.0f);

	switch (axis) {
	case Axis::Yaw:
		this->motors.yaw(std::min(targetPower, 0.1f));
	case Axis::Pitch:
		this->motors.pitch(- targetPower);
	case Axis::Roll:
		this->motors.roll(- targetPower);
	}
}
