/*
 Name:		RelaisSwitch.cpp
 Created:	10/6/2019 12:16:27 PM
 Author:	Jens Marchewka
*/

#include "JTimeout.h"

JTimeout::JTimeout(unsigned long duration, bool isInitialPassing)
{
	_lastExecute = 0;
	_duration = duration;
	_isInitialPassing = isInitialPassing;
}

JTimeout::~JTimeout()
{
	
}

bool JTimeout::CanExecute()
{
	unsigned long ms = millis();
	if (ms - _lastExecute > _duration || (_isInitialPassing && _lastExecute == 0)) {
		_lastExecute = ms;
		return true;
	}

	return false;
}