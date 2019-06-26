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

int I2C::readAddress(unsigned char registry, unsigned char& data)
{
	unsigned char *inbuff, outbuff;
	int retVal = -1;
	struct i2c_rdwr_ioctl_data packets;
	struct i2c_msg messages[2];

	outbuff = registry;
	messages[0].addr = address;
	messages[0].flags = 0;
	messages[0].len = sizeof(outbuff);
	messages[0].buf = &outbuff;

	inbuff = &data;
	messages[1].addr = address;
	messages[1].flags = I2C_M_RD;
	messages[1].len = sizeof(*inbuff);
	messages[1].buf = inbuff;

	packets.msgs = messages;
	packets.nmsgs = 2;

	retVal = ioctl(file, I2C_RDWR, &packets);
	if (retVal < 0) {
		perror("Read from I2C Device failed");
	}

	return retVal;
}

int I2C::readAddress(int address, unsigned char & data)
{
	return readAddress((unsigned char)address, data);
}

uint8_t I2C::readAddress(int address)
{
	unsigned char charData;
	auto result = readAddress((unsigned char)address, charData);
	return charData;
}

std::vector<uint8_t> I2C::readLength(int registry, int length)
{
	unsigned char* data[length] = {};
	unsigned char* inbuff, outbuff;
	int retVal = -1;
	struct i2c_rdwr_ioctl_data packets;
	struct i2c_msg messages[2];

	outbuff = registry;
	messages[0].addr = address;
	messages[0].flags = 0;
	messages[0].len = sizeof(outbuff);
	messages[0].buf = &outbuff;

	inbuff = *data;
	messages[1].addr = address;
	messages[1].flags = I2C_M_RD;
	messages[1].len = sizeof(*inbuff);
	messages[1].buf = inbuff;

	packets.msgs = messages;
	packets.nmsgs = 2;

	retVal = ioctl(file, I2C_RDWR, &packets);
	if (retVal < 0) {
		perror("Read from I2C Device failed");
	}

	std::vector<uint8_t> returnVector = std::vector<uint8_t>{};

	for (int i = 0; i < length; i++) {
		returnVector.push_back((uint8_t)(*data[i]));
	}

	return returnVector;


	//union i2c_smbus_data data;
	//struct i2c_smbus_ioctl_data args;

	//args.read_write = I2C_SMBUS_READ;
	//args.command = address;
	//args.size = length + 1;
	//args.data = &data;
	//ioctl(file, I2C_SMBUS, &args);

	//std::vector<uint8_t> response;
	//for (int i = 0; i < length; i++) {
	//	response.push_back(data.block[i]);
	//}
	//return response;
}

int I2C::writeAddress(unsigned char registry, unsigned char data)
{
	unsigned char buff[2];
	int retVal = -1;
	struct i2c_rdwr_ioctl_data packets;
	struct i2c_msg messages[1];

	buff[0] = registry;
	buff[1] = data;

	messages[0].addr = address;
	messages[0].flags = 0;
	messages[0].len = sizeof(buff);
	messages[0].buf = buff;

	packets.msgs = messages;
	packets.nmsgs = 1;

	retVal = ioctl(file, I2C_RDWR, &packets);
	if (retVal < 0) {
		perror("Write to I2C Device failed");
	}

	return retVal;
}

int I2C::writeAddress(int address, unsigned char data)
{
	return writeAddress((unsigned char)address, data);
}

int I2C::writeAddress(int address, int data)
{
	return writeAddress((unsigned char)address, (unsigned char)data);
}
