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

public:
	I2C(int address);
	virtual ~I2C();

	int readAddress(unsigned char address);
	int readAddress(unsigned char address, unsigned char* buffer, int length);
	void writeAddress(unsigned char address, unsigned char data);

	int readBytes(unsigned char* buffer, int length);
	void writeBytes(unsigned char* bytes, int count);
};

