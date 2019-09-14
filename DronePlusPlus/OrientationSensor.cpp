#include "OrientationSensor.h"

#include <iostream>
#include <unistd.h>

OrientationSensor::OrientationSensor(int address): address(address)
{
	i2c = new I2C(address);
	init();
}


OrientationSensor::~OrientationSensor()
{
	delete i2c;
}

void OrientationSensor::init()
{
	sleep(1);
	i2c->writeAddress((int)OrientationSensorRegisters::BNO055_OPR_MODE_ADDR, (int)OrientationSensorOperationModes::OPERATION_MODE_CONFIG);
	int value = i2c->readAddress((int)OrientationSensorRegisters::BNO055_OPR_MODE_ADDR);
	std::cout << "Operation mode set to ";
	printf("%02x\n", value);
	sleep(1);

	i2c->writeAddress((int)OrientationSensorRegisters::BNO055_SYS_TRIGGER_ADDR, 0x20);
	sleep(5);


	while (i2c->readAddress((int)OrientationSensorRegisters::BNO055_CHIP_ID_ADDR) != BNO055_ID)
	{
		sleep(0.001);
	}
	sleep(0.05);

	value = i2c->readAddress((int)OrientationSensorRegisters::BNO055_SYS_TRIGGER_ADDR);
	// std::cout << "Set sys trigger to ";
	// printf("%02x\n", value);
	sleep(1);

	i2c->writeAddress((int)OrientationSensorRegisters::BNO055_PWR_MODE_ADDR, (int)OrientationSensorPowerModes::POWER_MODE_NORMAL);
	value = i2c->readAddress((int)OrientationSensorRegisters::BNO055_PWR_MODE_ADDR);
	std::cout << "Set normal power mode ";
	printf("%02x\n", value);
	sleep(1);

	i2c->writeAddress((int)OrientationSensorRegisters::BNO055_PAGE_ID_ADDR, 0);
	value = i2c->readAddress((int)OrientationSensorRegisters::BNO055_PAGE_ID_ADDR);
	std::cout << "Set page address ";
	printf("%02x\n", value);
	sleep(1);

	i2c->writeAddress((int)OrientationSensorRegisters::BNO055_SYS_TRIGGER_ADDR, 0x0);
	value = i2c->readAddress((int)OrientationSensorRegisters::BNO055_SYS_TRIGGER_ADDR);
	std::cout << "Set sys trigger to ";
	printf("%02x\n", value);
	sleep(1);

	i2c->writeAddress((int)OrientationSensorRegisters::BNO055_OPR_MODE_ADDR, (int)OrientationSensorOperationModes::OPERATION_MODE_NDOF);
	value = i2c->readAddress((int)OrientationSensorRegisters::BNO055_OPR_MODE_ADDR);
	std::cout << "Operation mode set to ";
	printf("%02x\n", value);
	sleep(1);
}

union sixteenBitValue {
	int i;
	unsigned char c[2];
};

int16_t convert8to16bit(uint8_t lsb, uint8_t msb) {
	int16_t value = (((int16_t)lsb) | ((int16_t)msb) << 8);
	return value;
}


Orientation OrientationSensor::getOrientation()
{
	unsigned char bytes[6] = { 0 };
	i2c->readAddress((int)OrientationSensorRegisters::BNO055_EULER_H_LSB_ADDR, bytes, 6);

	auto yaw = convert8to16bit(bytes[0], bytes[1]);
	auto pitch = convert8to16bit(bytes[2], bytes[3]);
	auto roll = convert8to16bit(bytes[4], bytes[5]);

	return Orientation(((double)yaw) / 16.0 , ((double)pitch) / 16.0, ((double)roll) / 16.0);
}
