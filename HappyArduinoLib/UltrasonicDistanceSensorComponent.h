#pragma once

#include "Component.h"

class UltrasonicDistanceSensorComponent : public Component
{
public:
	UltrasonicDistanceSensorComponent( const char* _name, int _pinTrigger, int _pinEcho );
	
	// Component
	virtual void Init() override;
	virtual void OnFrame() override;
	virtual void GetKeyValues( KeyValue *keyValues, short &size ) override;
	
	long GetDistance() { return distance; };

private:
	int pinTrigger;
	int pinEcho;
	long distance;
};