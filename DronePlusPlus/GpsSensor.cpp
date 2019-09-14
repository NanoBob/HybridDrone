#include "GpsSensor.h"
#include <iostream>

GpsSensor::GpsSensor()
{
}

void GpsSensor::measure()
{
	bool fullRead = false;
	while (!fullRead) {
		auto byte = this->uart.readByte();
		if (this->gps.encode(byte)) {
			fullRead = true;
		}
	}

	if (gps.location.isValid()) {
		this->longitude = gps.location.lng();
		this->latitude = gps.location.lat();
	}
}

void GpsSensor::displayInfo()
{
	std::cout << "Location: " << "\n";
	if (gps.location.isValid())
	{
		std::cout << "Latitude: " << gps.location.lat() << ", Longitude: " << gps.location.lng() << "\n";
	}
	else
	{
		std::cout << "INVALID" << "\n";
	}

	std::cout << "\nDate/Time: " << "\n";
	if (gps.date.isValid())
	{
		std::cout << gps.date.day() << "-" << gps.date.month() << "-" << gps.date.year() << "\n";
	}
	else
	{
		std::cout << "INVALID" << "\n";
	}

	if (gps.time.isValid())
	{
		int hour = gps.time.hour();
		int minute = gps.time.minute();
		int second = gps.time.second();
		int centiSecond = gps.time.centisecond();

		std::string timeString =
			(hour < 10 ? "0" + std::to_string(hour) : std::to_string(hour)) + ":" +
			(minute < 10 ? "0" + std::to_string(minute) : std::to_string(minute)) + ":" +
			(second < 10 ? "0" + std::to_string(second) : std::to_string(second));

		std::cout << timeString << "\n\n";
	}
	else
	{
		std::cout << "INVALID" << "\n\n";
	}
}
