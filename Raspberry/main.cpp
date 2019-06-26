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
void motorTest() {
	MotorController controller = MotorController();
}

void orientationTest() {
	OrientationSensor sensor = OrientationSensor(0x28);

	while (true) {
		Orientation orientation = sensor.getOrientation();
		std::cout << "Yaw: " << orientation.yaw << ", Pitch: " << orientation.pitch << ", Roll: " << orientation.roll << std::endl;
		usleep(100000);
	}
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

void miscTest() {
	//I2C i2c = I2C(0x28);
	//unsigned char value = 0;

	//i2c.writeAddress(0x3D, 0x00);
	//sleep(1);
	//i2c.writeAddress(0x3F, 0x20);
	//sleep(1);
	//i2c.writeAddress(0x3E, 0x00);
	//sleep(1);
	//i2c.writeAddress(0x07, 0x00);
	//sleep(1);
	//i2c.writeAddress(0x3F, 0x00);
	//sleep(1);
	//i2c.writeAddress(0x3D, 0x0c);
	//sleep(1);


	//while (true) {
	//	i2c.readAddress(0X1A, value);
	//	std::cout << "Value: " << std::hex << (0xFF & value) << std::endl;
	//}



	//GPIOPin* gpio4 = new GPIOPin("4"); //create new GPIOPin object to be attached to  GPIOPin4
	//GPIOPin* gpio17 = new GPIOPin("17"); //create new GPIOPin object to be attached to  GPIOPin17

	//gpio4->enable(); //export GPIOPin4
	//gpio17->enable(); //export GPIOPin17

	//std::cout << " GPIOPin pins exported" << std::endl;

	//gpio17->setDirection("in"); //GPIOPin4 set to output
	//gpio4->setDirection("out"); // GPIOPin17 set to input

	//std::cout << " Set GPIOPin pin directions" << std::endl;

	//while (1)
	//{
	//	usleep(500000);  // wait for 0.5 seconds
	//	gpio17->read(inputstate); //read state of GPIOPin17 input pin
	//	std::cout << "Current input pin state is " << inputstate << std::endl;
	//	if (inputstate == "0") // if input pin is at state "0" i.e. button pressed
	//	{
	//		std::cout << "input pin state is \"Pressed\".n Will check input pin state again in 20ms " << std::endl;
	//		usleep(20000);
	//		std::cout << "Checking again ....." << std::endl;
	//		gpio17->read(inputstate); // checking again to ensure that state "0" is due to button press and not noise
	//		if (inputstate == "0")
	//		{
	//			std::cout << "input pin state is definitely \"Pressed\". Turning LED ON" << std::endl;
	//			gpio4->write("1"); // turn LED ON

	//			std::cout << " Waiting until pin is unpressed....." << std::endl;
	//			while (inputstate == "0") {
	//				gpio17->read(inputstate);
	//			};
	//			std::cout << "pin is unpressed" << std::endl;

	//		}
	//		else
	//			std::cout << "input pin state is definitely \"UnPressed\". That was just noise." << std::endl;

	//	}
	//	gpio4->write("0");

	//}
	//std::cout << "Exiting....." << std::endl;
}

int main() {
	motorTest();
	orientationTest();
	return 0;
}
