/*
 Name:		SonarSwitch.cpp
 Created:	10/6/2019 12:16:27 PM
 Author:	Jens Marchewka
*/

#include "SonarSwitch.h"

SonarSwitch::SonarSwitch(unsigned int threshold, unsigned int minDistance, unsigned int maxDistance, unsigned long probeDelay)
{
	_probeDelay = probeDelay;
	_probed = 0;
	_maxDistance = maxDistance;
	_minDistance = minDistance;
	_lastDistancesCount = threshold;
	_lastDistances = new int[_lastDistancesCount];
	_lastState = false;
	_minDistances = minDistance * threshold;
	_maxDistances = maxDistance * threshold;
	for (unsigned int i = 0; i < _lastDistancesCount; i++)
	{
		_lastDistances[i] = 0;
	}
}
SonarSwitch::~SonarSwitch()
{
	delete _lastDistances, _lastDistancesCount;
}

bool SonarSwitch::Switch(unsigned int distance)
{
	unsigned long elapsedMillisSinceProbe = millis() - _probed;
	if (elapsedMillisSinceProbe < _probeDelay) {
		return false;
	}

	_probed = millis();

	PushDistance(distance);

	return ShouldSwitch();
}

void SonarSwitch::PushDistance(unsigned int dist)
{
	unsigned int last = dist;
	for (int i = 0; i < _lastDistancesCount; i++)
	{
		unsigned int current = _lastDistances[i];
		_lastDistances[i] = last;
		last = current;
	}
}

// Calculate the probability of the objects distance relative to the min / max distance given within the record of distances. Does this make sense?
float SonarSwitch::Probability()
{
	float dist = 0;
	for (int i = 0; i < _lastDistancesCount; i++)
	{
		dist += _lastDistances[i];
	}

	if (dist >= _maxDistances)
		return 0;
	if (dist < _minDistances)
		return 0;

	float cap = (_maxDistances - _minDistances) / 2;
	dist = dist - _minDistances;
	float value = abs(dist - cap);

	return 1 - (value / cap);
}

bool SonarSwitch::ShouldSwitch()
{
	if (Probability() < 0.1)
	{
		_lastState = false;
		return false;
	}

	// last state indicates that we already switched to true 
	// and the object was not moved since then so we dont
	// want to trigger anymore. 
	if (_lastState)
	{
		return false;
	}

	_lastState = true;
	return true;
}