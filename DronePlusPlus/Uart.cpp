#include "Uart.h"

Uart::Uart()
{

	uart0_filestream = open("/dev/serial0", O_RDWR | O_NOCTTY);
	if (uart0_filestream == -1)
	{
		printf("Error - Unable to open UART.  Ensure it is not in use by another application\n");
	}

	struct termios options;
	tcgetattr(uart0_filestream, &options);
	options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;
	options.c_iflag = IGNPAR;
	options.c_oflag = 0;
	options.c_lflag = 0;
	tcflush(uart0_filestream, TCIFLUSH);
	tcsetattr(uart0_filestream, TCSANOW, &options);
}

void Uart::readBytes(unsigned char* buffer, int length)
{
	for (int i = 0; i < length; i++) {
		buffer[i] = readByte();
	}
}

unsigned char Uart::readByte()
{
	if (uart0_filestream != -1)
	{
		unsigned char rx_buffer[2];
		int rx_length = read(uart0_filestream, (void*)rx_buffer, 1);
		if (rx_length < 0)
		{
			
		}
		else if (rx_length == 0)
		{
			
		}
		else
		{
			rx_buffer[rx_length] = '\0';
			return rx_buffer[0];
		}
	}
}
