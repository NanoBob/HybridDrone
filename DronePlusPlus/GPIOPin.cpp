#include "GPIOPin.h"

using namespace std;

GPIOPin::GPIOPin()
{
}

GPIOPin::GPIOPin(string number) : state(GPIOPinState::DISABLED), number(number)
{

}

bool GPIOPin::enable()
{
	string export_str = "/sys/class/gpio/export";
	ofstream exportgpio(export_str.c_str());
	if (!exportgpio) {
		cout << " OPERATION FAILED: Unable to export GPIOPin" << this->number << " ." << endl;
		return false;
	}

	exportgpio << this->number;
	exportgpio.close();
	return true;
}

bool GPIOPin::disable()
{
	string unexport_str = "/sys/class/gpio/unexport";
	ofstream unexportgpio(unexport_str.c_str());
	if (!unexportgpio) {
		cout << " OPERATION FAILED: Unable to unexport GPIOPin" << this->number << " ." << endl;
		return false;
	}

	unexportgpio << this->number;
	unexportgpio.close();
	return true;
}

bool GPIOPin::setDirection(GPIOPinDirection direction)
{

	string setdir_str = "/sys/class/gpio/gpio" + this->number + "/direction";
	ofstream setdirgpio(setdir_str.c_str()); 

	if (!setdirgpio) {
		cout << " OPERATION FAILED: Unable to set direction of GPIOPin" << this->number << " ." << endl;
		return false;
	}

	setdirgpio << (direction == GPIOPinDirection::IN ? "in" : "out");
	setdirgpio.close();
	return true;
}

bool GPIOPin::write(GPIOPinValue value)
{

	string setval_str = "/sys/class/gpio/gpio" + this->number + "/value";
	ofstream setvalgpio(setval_str.c_str()); 

	if (!setvalgpio) {
		cout << " OPERATION FAILED: Unable to set the value of GPIOPin" << this->number << " ." << endl;
		return false;
	}

	setvalgpio << (value == GPIOPinValue::HIGH ? "1" : "0");
	setvalgpio.close();
	return true;
}

GPIOPinValue GPIOPin::read() {

	string getval_str = "/sys/class/gpio/gpio" + this->number + "/value";
	ifstream getvalgpio(getval_str.c_str());

	if (!getvalgpio) {
		cout << " OPERATION FAILED: Unable to get value of GPIOPin" << this->number << " ." << endl;
		return GPIOPinValue::UNKNOWN;
	}

	std::string stringValue;
	getvalgpio >> stringValue;
	getvalgpio.close();

	return stringValue == "1" ? GPIOPinValue::HIGH : GPIOPinValue::LOW;
}

string GPIOPin::getNumber() {

	return this->number;

}

GPIOPinState GPIOPin::getState()
{
	return state;
}
