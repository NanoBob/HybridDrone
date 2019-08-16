#include <iostream>
#include <string>

#include <chrono>
#include <thread>

#include "MotorController.h"
#include "OrientationController.h"

MotorController* motorController;
OrientationController* orientationController;

extern "C" void init() {
	motorController = new MotorController();
	orientationController = new OrientationController(*motorController);
}

// motors

extern "C" void setYaw(float value) {
	motorController->yaw(value);
}

extern "C" void setPitch(float value) {
	motorController->pitch(value);
}

extern "C" void setRoll(float value) {
	motorController->roll(value);
}

extern "C" void setThrottle(float value) {
	motorController->throttle(value);
}

extern "C" void getMotorThrottles(float& frontLeft, float& frontRight, float& rearLeft, float& rearRight) {
	if (motorController != nullptr && motorController->isInitialized()) {
		frontLeft = motorController->frontLeft->getSpeed();
		frontRight = motorController->frontRight->getSpeed();
		rearLeft = motorController->rearLeft->getSpeed();
		rearRight = motorController->rearRight->getSpeed();
	}
}

extern "C" void runTest(float value) {
	motorController->test(value);
}

extern "C" void disableMotors() {
	motorController->disable();
}

extern "C" void enableMotors() {
	motorController->enable();
}

// orientation

extern "C" void startOrientationThread() {
	orientationController->start();
}

extern "C" void stopOrientationThread() {
	orientationController->stop();
}

extern "C" void startOrientationAssist() {
	orientationController->startOrientationAssist();
}

extern "C" void stopOrientationAssist() {
	orientationController->stopOrientationAssit();
}

extern "C" void setTargetOrientation(float yaw, float pitch, float roll) {
	orientationController->setTargetOrientation(Orientation(yaw, pitch, roll));
}

extern "C" void getOrientation(float& yaw, float& pitch, float& roll) {
	auto orientation = orientationController->getOrientation();

	yaw = orientation.yaw;
	pitch = orientation.pitch;
	roll = orientation.roll;
}