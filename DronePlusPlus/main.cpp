#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "GPIOPin.h"
#include "I2C.h"
#include <ios>
#include "OrientationSensor.h"
#include "MotorController.h"
#include "OrientationController.h"

void motorTest() {
	//MotorController controller = MotorController();
}

void orientationTest() {
	MotorController motorController = MotorController();
	OrientationController controller = OrientationController(motorController);
	controller.start();
}

void gpioTest() {
	std::string inputstate;
	GPIOPin* pin = new GPIOPin("17");
	pin->enable();
	pin->setDirection(GPIOPinDirection::OUT);

	while (true) {
		pin->write(GPIOPinValue::HIGH);
		usleep(1000000);
		pin->write(GPIOPinValue::LOW);
		usleep(1000000);
	}
}

int main() {
	motorTest();
	orientationTest();
	return 0;
}
