#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

#pragma once
class Uart
{
private:
	int uart0_filestream;
public:
	Uart();

	void readBytes(unsigned char* buffer, int length);
	unsigned char readByte();

};

