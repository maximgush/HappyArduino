#pragma once

#include "Component.h"

#include <RTClib.h>
#include <Wire.h>

class RelayComponent : public Component
{
	bool isOn;
	int pin;
public:
	RelayComponent(const char* _name, int _pin)
		: Component(_name)	
		, pin()
		, isOn(false)
	{
	}
	virtual void Init()
	{
		pinMode(pin, OUTPUT);
		digitalWrite(pin, LOW);
	}
	virtual void OnFrame()
	{
		digitalWrite(pin, isOn ? HIGH : LOW);
	};
	
	bool IsOn() { return isOn; };
	
	void On() { isOn = true; digitalWrite(pin, HIGH);};
	void Off() { isOn = false; digitalWrite(pin, LOW); };
	
	virtual void GetKeyValues(KeyValue *keyValues, short &size) override
	{
		keyValues[size] = KeyValue("Включено", String(IsOn())); size++;
	};
	
};