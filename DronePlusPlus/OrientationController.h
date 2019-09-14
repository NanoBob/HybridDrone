#pragma once
#include "Orientation.h"
#include <thread>
#include "OrientationSensor.h"
#include "MotorController.h"


enum class Axis {
	Yaw, Pitch, Roll
};

class OrientationController
{
private:

	OrientationSensor sensor;
	MotorController& motors;

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
	OrientationController(MotorController& motors);
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