#include "PwmController.h"
#include <cmath>

PwmController::PwmController(int address) :
	i2c(address)
{
	init();
}

void PwmController::init()
{
	reset();
}

void PwmController::reset()
{
	i2c.writeAddress((int)PwmRegisters::MODE1, 0x0);
}

void PwmController::setPwm(uint8_t channel, uint16_t on, uint16_t off)
{
	i2c.writeAddress((int)PwmRegisters::LED0_ON_L + 4 * channel, (on & 0xff));
	i2c.writeAddress((int)PwmRegisters::LED0_ON_H + 4 * channel, (on >> 8));
	i2c.writeAddress((int)PwmRegisters::LED0_OFF_L + 4 * channel, (off & 0xff));
	i2c.writeAddress((int)PwmRegisters::LED0_OFF_H + 4 * channel, (off >> 8));
}

void PwmController::setAllPwm(uint16_t on, uint16_t off)
{
	i2c.writeAddress((int)PwmRegisters::ALL_LED_ON_L, (on & 0xff));
	i2c.writeAddress((int)PwmRegisters::ALL_LED_ON_H, (on >> 8));
	i2c.writeAddress((int)PwmRegisters::ALL_LED_OFF_L, (off & 0xff));
	i2c.writeAddress((int)PwmRegisters::ALL_LED_OFF_H, (off >> 8));
}

void PwmController::setPulseParameters(int pin, double dutyCycle, bool invertPolarity)
{
	uint16_t value = (uint16_t) std::min(dutyCycle, 4095.0);
	uint8_t channel = (uint8_t)pin;

	if (channel > 15) {
		throw std::runtime_error("Channel must be between 0 and 15");
	}

	if (invertPolarity) {
		switch (value)
		{
		case 0:
			setPwm(channel, 4095, 0);
			break;
		case 4095:
			setPwm(channel, 0, 4095);
			break;
		case 4096:
			setPwm(channel, 0, 4096);
			break;
		default:
			setPwm(channel, 0, (ushort)(4095 - value));
			break;
		}
	}
	else {
		switch (value)
		{
		case 4095:
			setPwm(channel, 4095, 0);
			break;
		case 4096:
			setPwm(channel, 4096, 0);
			break;
		case 0:
			setPwm(channel, 0, 4095);
			break;
		default:
			setPwm(channel, 0, value);
			break;
		}
	}
}

void PwmController::setDesiredFrequency(double frequency)
{
	frequency *= 0.9f;  // Correct for overshoot in the frequency setting (see issue #11).
	double prescaleval = 25000000;
	prescaleval /= 4096;
	prescaleval /= frequency;
	prescaleval -= 1;

	uint8_t prescale = (uint8_t)std::floor(prescaleval + 0.5f);

	int oldMode= i2c.readAddress((int)PwmRegisters::MODE1);
	int newMode = (oldMode & 0x7f) | 0x10;

	i2c.writeAddress((int)PwmRegisters::MODE1, newMode);
	i2c.writeAddress((int)PwmRegisters::PRESCALE, prescale);
	i2c.writeAddress((int)PwmRegisters::MODE1, oldMode);

	i2c.writeAddress((int)PwmRegisters::MODE1, oldMode | 0xa1);
}
