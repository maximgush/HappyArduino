#pragma once

#include "Component.h"

class WaterLevelSensorComponent : public Component
{
private:
	short value;
	short pin;
public:
	WaterLevelSensorComponent(const char* _name, short _pin)
		: Component(_name)
		, pin(_pin)
		, value(-1)
	{		
	}
	
	virtual void OnFrame()
	{
		value = analogRead(pin);	
	};
	
	virtual void GetKeyValues(KeyValue *keyValues, short &size) override
	{
		keyValues[size] = KeyValue("Аналоговое значение", String(value,DEC)); size++;
	};
	
	int GetValue()
	{
		return value;
	}
};