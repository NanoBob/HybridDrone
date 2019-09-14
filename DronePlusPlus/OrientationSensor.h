#pragma once
#include "I2C.h"
#include "Orientation.h"
#include "OrientationSensorEnums.h"
#include <cstring>
#include <math.h>

class OrientationSensor
{
private:
	int address;
	I2C i2c;

	void init();
public:
	OrientationSensor(int address);

	Orientation getOrientation();
};

