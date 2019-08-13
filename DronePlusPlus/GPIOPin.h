#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include "GPIOPinEnum.h"

class GPIOPin
{
public:
	GPIOPin();
	GPIOPin(std::string x);

	bool enable();
	bool disable();

	bool setDirection(GPIOPinDirection direction);

	bool write(GPIOPinValue value);
	GPIOPinValue read();

	std::string getNumber();
	GPIOPinState getState();

private:
	GPIOPinState state;
	std::string number;
};

