#pragma once

#include "Orientation.h"
#include "OrientationSensor.h"
#include "MotorController.h"

#include <thread>
#include <memory>

enum class Axis {
	Yaw, Pitch, Roll
};

class OrientationController
{
private:

	OrientationSensor sensor;
	std::shared_ptr<MotorController> motors;

	Orientation orientation;
	Orientation targetOrientation;

	bool isRunning;
	float orientationAssistAgression;
	int readCount;

	bool terminateSensorThread;
	std::thread* sensorThread;

	bool terminateMotorThread;
	std::thread* motorThread;

	Orientation sanitizeOrientation(Orientation orientation);
	void runOrientation();
	void runMotors();

	void performStabilityAssist();
	void handleAxisOffset(Axis axis, float offset);
public:
	OrientationController(std::shared_ptr<MotorController> motors);
	~OrientationController();

	void start();
	void stop();

	void startOrientationAssist();
	void stopOrientationAssit();

	Orientation getOrientation();
	Orientation getTargetOrientation();
	void setTargetOrientation(Orientation orientation);
	void setOrientationAssistAgression(float value);

};