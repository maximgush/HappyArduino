#pragma once

#inclide "IOnOff.h"
#include "Component.h"

class RelayComponent : public IOnOff, public Component
{
	bool isOn;
	int pin;
public:
	RelayComponent(const char* _name, int _pin, _isOn = false)
		: Component(_name)	
		, pin(_pin)
		, isOn(_isOn)
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