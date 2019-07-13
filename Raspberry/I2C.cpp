#include "I2C.h"
#include <iostream>

using namespace std;


I2C::I2C(int address = 0x40) : address(address)
{
	openBus();
	acquireDevice();
}


I2C::~I2C()
{
}

void I2C::openBus()
{
	char *filename = (char*)"/dev/i2c-1";
	file = open(filename, O_RDWR);
	if (file < 0)
	{
		//ERROR HANDLING: you can check errno to see what went wrong
		printf("Failed to open the i2c bus");
		std::cout << file << endl;
		return;
	}
}

void I2C::acquireDevice()
{
	if (ioctl(file, I2C_SLAVE, address) < 0)
	{
		printf("Failed to acquire bus access and/or talk to slave.\n");
		std::cout << file << endl;
		//ERROR HANDLING; you can check errno to see what went wrong
		return;
	}
}

//int I2C::readAddress(unsigned char registry, unsigned char& data)
//{
//	unsigned char *inbuff, outbuff;
//	int retVal = -1;
//	struct i2c_rdwr_ioctl_data packets;
//	struct i2c_msg messages[2];
//
//	outbuff = registry;
//	messages[0].addr = address;
//	messages[0].flags = 0;
//	messages[0].len = sizeof(outbuff);
//	messages[0].buf = &outbuff;
//
//	inbuff = &data;
//	messages[1].addr = address;
//	messages[1].flags = I2C_M_RD;
//	messages[1].len = sizeof(*inbuff);
//	messages[1].buf = inbuff;
//
//	packets.msgs = messages;
//	packets.nmsgs = 2;
//
//	retVal = ioctl(file, I2C_RDWR, &packets);
//	if (retVal < 0) {
//		perror("Read from I2C Device failed");
//	}
//
//	return retVal;
//}
//
//int I2C::readAddress(int address, unsigned char & data)
//{
//	return readAddress((unsigned char)address, data);
//}
//
//uint8_t I2C::readAddress(int address)
//{
//	unsigned char charData;
//	auto result = readAddress((unsigned char)address, charData);
//	return charData;
//}
//
//int I2C::writeAddress(unsigned char address, unsigned char data)
//{
//	unsigned char buffer[2] = {
//		address,
//		data
//	};
//	writeBytes(buffer, 2);
//}

int I2C::readAddress(int address)
{
	unsigned char buffer[1] = { 0 };
	readAddress(address, buffer, 1);
	return buffer[0];
}

int I2C::readAddress(int address, unsigned char* buffer, int length)
{
	unsigned char writeBuffer[1] = {
		address,
	};
	writeBytes(writeBuffer, 1);

	int bytesRead = read(file, buffer, length);
	if (bytesRead != length) {
		std::printf("Failed to read bytes");
	}
	return bytesRead;
}

int I2C::writeAddress(int address, int data)
{
	unsigned char buffer[2] = {
		address,
		data
	};
	writeBytes(buffer, 2);
}

int I2C::readBytes(unsigned char* buffer, int length)
{
	int bytesRead = read(file, buffer, length);
	if (bytesRead != length) {
		std::printf("Failed to read bytes");
	}
	return bytesRead;
}

void I2C::writeBytes(unsigned char* buffer, int count)
{
	if (write(file, buffer, count) != count)
	{
		printf("Failed to write to the i2c bus.\n");
	}
}