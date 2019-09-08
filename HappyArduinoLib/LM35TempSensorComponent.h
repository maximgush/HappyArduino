#pragma once

#include "Component.h"

class LM35TempSensorComponent : public Component
{
private:
	short pin;
	short analogValue;// define variable
	short temperature;
public:
	LM35TempSensorComponent(const char* _name, short _pin)
		: Component(_name)
		, pin(_pin)
		, temperature(-273)
	{				
	}
	
	virtual void OnFrame()
	{
		analogValue = analogRead(pin);
		temperature = (125 * analogValue) >> 8;
	};
	
	virtual void GetKeyValues(KeyValue *keyValues, short &size) override
	{
		keyValues[size] = KeyValue("Аналоговое значение", String(analogValue, DEC)); size++;
		keyValues[size] = KeyValue("Температура", String(temperature, DEC) + " °С"); size++;
	};
	
	int GetTemperature()
	{
		return temperature;
	}
};