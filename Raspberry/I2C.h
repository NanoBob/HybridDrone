#pragma once
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>

#include <string>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

#include <vector>

class I2C
{
private:
	int address;
	int file;

	void openBus();
	void acquireDevice();

	int readAddress(unsigned char address, unsigned char& data);
	int readAddress(int address, unsigned char& data);
public:
	I2C(int address);
	virtual ~I2C();

	uint8_t readAddress(int address);
	std::vector<uint8_t> readLength(int address, int length);

	int writeAddress(unsigned char address, unsigned char data);
	int writeAddress(int address, unsigned char data);
	int writeAddress(int address, int data);
};

