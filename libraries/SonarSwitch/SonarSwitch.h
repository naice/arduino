/*
 Name:		SonarSwitch.h
 Created:	10/6/2019 12:16:27 PM
 Author:	imnai
 Editor:	http://www.visualmicro.com
*/

#ifndef _SonarSwitch_h
#define _SonarSwitch_h
#include "arduino.h"

class SonarSwitch {
public:
	SonarSwitch(unsigned int threshold, unsigned int minDistance, unsigned int maxDistance, unsigned long probeDelay = 5);
	~SonarSwitch();
	bool Switch(unsigned int distance);
	float Probability();
private:
	int * _lastDistances;
	unsigned int _lastDistancesCount;
	unsigned int _minDistance;
	unsigned int _maxDistance;
	unsigned int _minDistances;
	unsigned int _maxDistances;
	bool _lastState;
	unsigned long _probeDelay;
	unsigned long _probed;

	void PushDistance(unsigned int dist);
	bool ShouldSwitch();
};

#endif

