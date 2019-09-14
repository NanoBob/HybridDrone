#pragma once

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

	int readAddress(int address);
	int readAddress(int address, unsigned char* buffer, int length);
	int writeAddress(int address, int data);

	int readBytes(unsigned char* buffer, int length);
	void writeBytes(unsigned char* bytes, int count);
};

