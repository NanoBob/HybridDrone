#pragma once

#include "Gps.h"
#include "Uart.h"

class GpsSensor
{
private:
	TinyGPSPlus gps;
	Uart uart;
public:
	GpsSensor();

	void measure();
	void displayInfo();

	float longitude;
	float latitude;
};

