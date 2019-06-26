#include "OrientationSensor.h"
#include <iostream>

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
	//if (value > 0x8000) {
	//	std::cout << "OVER 0x8000\n";
	//	value -= 65536;
	//}
	return value;
}


Orientation OrientationSensor::getOrientation()
{
	//auto bytes = i2c->readLength((int)OrientationSensorRegisters::BNO055_EULER_H_LSB_ADDR, 6);

	//for (auto byte : bytes) {
	//	printf("%02x ", byte);
	//}

	//auto yaw = convert8to16bit(bytes[0], bytes[1]);
	//auto pitch = convert8to16bit(bytes[2], bytes[3]);
	//auto roll = convert8to16bit(bytes[4], bytes[5]);

	uint8_t yawLSB = i2c->readAddress((int)OrientationSensorRegisters::BNO055_EULER_H_LSB_ADDR);
	uint8_t yawMSB = i2c->readAddress((int)OrientationSensorRegisters::BNO055_EULER_H_MSB_ADDR);

	uint8_t pitchLSB = i2c->readAddress((int)OrientationSensorRegisters::BNO055_EULER_P_LSB_ADDR);
	uint8_t pitchMSB = i2c->readAddress((int)OrientationSensorRegisters::BNO055_EULER_P_MSB_ADDR);

	uint8_t rollLSB = i2c->readAddress((int)OrientationSensorRegisters::BNO055_EULER_R_LSB_ADDR);
	uint8_t rollMSB = i2c->readAddress((int)OrientationSensorRegisters::BNO055_EULER_R_MSB_ADDR);

	int16_t yaw = convert8to16bit(yawLSB, yawMSB);
	int16_t pitch = convert8to16bit(pitchLSB, pitchMSB);
	int16_t roll = convert8to16bit(rollLSB, rollMSB);

	yaw = (yaw > 180 * 16 ? convert8to16bit(yawLSB, yawMSB - 0x80) : yaw < -180 * 16 ? convert8to16bit(yawLSB, yawMSB - 0x80) : yaw) % (360 * 16);
	roll = (roll > 180 * 16 ? convert8to16bit(rollLSB, rollMSB - 0x80) : roll < -180 * 16 ? convert8to16bit(rollLSB, rollMSB - 0x80) : roll) % (360 * 16);

	printf("\n%02x ", yawMSB);
	printf("%02x\t\t", yawLSB);
	printf("%02x: ", yaw);
	std::cout << yaw << "\n";

	printf("%02x ", pitchMSB);
	printf("%02x\t\t", pitchLSB);
	printf("%02x: ", pitch);
	std::cout << pitch << "\n";

	printf("%02x ", rollMSB);
	printf("%02x\t\t", rollLSB);
	printf("%02x: ", roll);
	std::cout << roll << "\n";

	return Orientation(((double)yaw) / 16.0 , ((double)pitch) / 16.0, ((double)roll) / 16.0);
}


//Orientation OrientationSensor::getOrientation()
//{
//	//printf("Reading bytes");
//	//auto bytes = i2c->readLength((int)OrientationSensorRegisters::BNO055_EULER_H_LSB_ADDR, 6);
//	//printf("Bytes read");
//
//	//auto yaw = convert8to16bit(bytes[0], bytes[1]);
//	//auto pitch = convert8to16bit(bytes[2], bytes[3]);
//	//auto roll = convert8to16bit(bytes[4], bytes[5]);
//
//
//	float x, y, z, w;
//	x = y = z = w = 0;
//
//	auto wLSB = i2c->readAddress((int)OrientationSensorRegisters::BNO055_QUATERNION_DATA_W_LSB_ADDR);
//	auto wMSB = i2c->readAddress((int)OrientationSensorRegisters::BNO055_QUATERNION_DATA_W_MSB_ADDR);
//	auto xLSB = i2c->readAddress((int)OrientationSensorRegisters::BNO055_QUATERNION_DATA_X_LSB_ADDR);
//	auto xMSB = i2c->readAddress((int)OrientationSensorRegisters::BNO055_QUATERNION_DATA_X_MSB_ADDR);
//	auto yLSB = i2c->readAddress((int)OrientationSensorRegisters::BNO055_QUATERNION_DATA_Y_LSB_ADDR);
//	auto yMSB = i2c->readAddress((int)OrientationSensorRegisters::BNO055_QUATERNION_DATA_Y_MSB_ADDR);
//	auto zLSB = i2c->readAddress((int)OrientationSensorRegisters::BNO055_QUATERNION_DATA_Z_LSB_ADDR);
//	auto zMSB = i2c->readAddress((int)OrientationSensorRegisters::BNO055_QUATERNION_DATA_Z_MSB_ADDR);
//
//
//	const double scale = (1.0 / (1 << 14));
//
//	w = ((((uint16_t)wMSB) << 8) | ((uint16_t)wLSB)) * scale;
//	x = ((((uint16_t)xMSB) << 8) | ((uint16_t)xLSB)) * scale;
//	y = ((((uint16_t)yMSB) << 8) | ((uint16_t)yLSB)) * scale;
//	z = ((((uint16_t)zMSB) << 8) | ((uint16_t)zLSB)) * scale;
//
//
//	//w = convert8to16bit(wLSB, wMSB) * scale;
//	//x = convert8to16bit(xLSB, xMSB) * scale;
//	//y = convert8to16bit(yLSB, yMSB) * scale;
//	//z = convert8to16bit(zLSB, zMSB) * scale;
//
//	std::cout << w << ", " << x << ", " << y << ", " << z << "\n";
//
//
//	double sqw = w * w;
//	double sqx = x * x;
//	double sqy = y * y;
//	double sqz = z * z;
//
//	float roll = atan2(2.0 * (x * y + z * w), (sqx - sqy - sqz + sqw));
//	float pitch = asin(-2.0 * (x * z - y * w) / (sqx + sqy + sqz + sqw));
//	float yaw = atan2(2.0 * (y * z + x * w), (-sqx - sqy + sqz + sqw));
//
//	return Orientation(yaw, pitch, roll);
//}

