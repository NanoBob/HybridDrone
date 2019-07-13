#include <iostream>
#include <string>

#include <chrono>
#include <thread>

#include "MotorController.h"
#include "OrientationController.h"

MotorController* motorController;
OrientationController* orientationController;

void init() {
	motorController = new MotorController();
	orientationController = new OrientationController(*motorController);

	orientationController->start();
}

// motors

void setYaw(float value) {
	motorController->yaw(value);
}

void setPitch(float value) {
	motorController->pitch(value);
}

void setRoll(float value) {
	motorController->roll(value);
}

void setThrottle(float value) {
	motorController->throttle(value);
}

// orientation

void startOrientationThread() {
	orientationController->start();
}

void stopOrientationThread() {
	orientationController->stop();
}

void setTargetOrientation(float yaw, float pitch, float roll) {
	orientationController->setTargetOrientation(Orientation(yaw, pitch, roll));
}

void getOrientation(float& yaw, float& pitch, float& roll) {
	auto orientation = orientationController->getOrientation();

	yaw = orientation.yaw;
	pitch = orientation.pitch;
	roll = orientation.roll;
}