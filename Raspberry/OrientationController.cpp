#include "OrientationController.h"
#include <iostream>

OrientationController::OrientationController(MotorController& motors) : isRunning(false), orientation(0, 0, 0), targetOrientation(0, 0, 0), terminateThread(false), motors(motors)
{
	sensor = new OrientationSensor(0x28);
}

OrientationController::~OrientationController()
{
	terminateThread = true;
	if (sensorThread != nullptr) {
		sensorThread->join();
		delete sensorThread;
	}

	delete sensor;
}

void OrientationController::start()
{
	isRunning = true;
	sensorThread = new std::thread([this] { this->run(); });
}

void OrientationController::stop()
{
	isRunning = false;
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

Orientation OrientationController::sanitizeOrientation(Orientation orientation)
{
	float yawDiff = std::abs(orientation.yaw - this->orientation.yaw);
	float pitchDiff = std::abs(orientation.pitch - this->orientation.pitch);
	float rollDiff = std::abs(orientation.roll - this->orientation.roll);

	if (yawDiff > 100) {
		orientation.yaw = this->orientation.yaw;
	}
	if (pitchDiff > 100) {
		orientation.pitch = this->orientation.pitch;
	}
	if (rollDiff > 100) {
		orientation.roll = this->orientation.roll;
	}
	//std::cout << "Diff Yaw: " << yawDiff << ", Pitch: " << pitchDiff << ", Roll: " << rollDiff << "\n";

	return orientation;
}

void OrientationController::run() {
	while (!terminateThread) {
		Orientation orientation = sensor->getOrientation();

		this->orientation = sanitizeOrientation(orientation);

		float yawDiff = this->targetOrientation.yaw - this->orientation.yaw;
		float pitchDiff = this->targetOrientation.pitch - this->orientation.pitch;
		float rollDiff = this->targetOrientation.roll - this->orientation.roll;

		//std::cout << "Yaw: " << orientation.yaw << ", Pitch: " << orientation.pitch << ", Roll: " << orientation.roll << "\n";

		usleep(10 * 1000);
	}
}
