/*
 Name:		RelaisSwitch.cpp
 Created:	10/6/2019 12:16:27 PM
 Author:	Jens Marchewka
*/

#include "RelaisSwitch.h"

RelaisSwitch::RelaisSwitch(unsigned int pin, bool defaultState, bool isDigital)
{
	_currentState = defaultState;
	_isDigital = isDigital;
	_pin = pin;
  	pinMode(_pin, OUTPUT);
	if (_currentState)
		Off();
	else
		On();
}
RelaisSwitch::~RelaisSwitch()
{
	
}

bool RelaisSwitch::Toggle()
{
	if (_currentState)
		Off();
	else
		On();
		
	return GetState();
}

bool RelaisSwitch::GetState()
{
	return _currentState;
}

void RelaisSwitch::On()
{
	if (_isDigital)
		digitalWrite(_pin, HIGH);
	else
		analogWrite(_pin, HIGH);

	_currentState = true;
}

void RelaisSwitch::Off()
{
	if (_isDigital)
		digitalWrite(_pin, LOW);
	else
		analogWrite(_pin, LOW);

	_currentState = false;
}