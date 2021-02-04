/*
 Name:		JTimeout.h
 Created:	10/6/2019 12:16:27 PM
 Author:	imnai
*/

#ifndef _JTimeout_h
#define _JTimeout_h
#include "arduino.h"

class JTimeout {
public:
	JTimeout(unsigned long duration, bool isInitialPassing = false);
	~JTimeout();
	bool CanExecute();
private:
	unsigned long _lastExecute;
	unsigned long _duration;
	bool _isInitialPassing;
};

#endif

