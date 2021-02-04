/*
 Name:		RelaisSwitch.h
 Created:	10/6/2019 12:16:27 PM
 Author:	imnai
 Editor:	http://www.visualmicro.com
*/

#ifndef _RelaisSwitch_h
#define _RelaisSwitch_h
#include "arduino.h"

class RelaisSwitch {
public:
	RelaisSwitch(unsigned int pin, bool defaultState = false, bool isDigital = true);
	~RelaisSwitch();
	bool Toggle();
	void On();
	void Off();
	bool GetState();
private:
	bool _currentState;
	bool _isDigital;
	int _pin;
};

#endif

