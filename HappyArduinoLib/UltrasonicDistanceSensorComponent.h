#pragma once

#include "Component.h"

class UltrasonicDistanceSensorComponent : public Component
{
	int pinTrigger;
	int pinEcho;
	long distance;
public:
	UltrasonicDistanceSensorComponent(const char* _name, int _pinTrigger, int _pinEcho)
		: Component(_name)	
		, pinTrigger(_pinTrigger)
		, pinEcho(_pinEcho)
		, distance(-1)
	{
	}
	virtual void Init()
	{
		pinMode(pinTrigger, OUTPUT);
		pinMode(pinEcho, INPUT);
		digitalWrite(pinTrigger, LOW);
		digitalWrite(pinEcho, LOW);
	}
	virtual void OnFrame()
	{
		 digitalWrite(pinTrigger, LOW); 
		 delayMicroseconds(2); 

		 digitalWrite(pinTrigger, HIGH);
		 delayMicroseconds(10); 
		 digitalWrite(pinTrigger, LOW);
		 long duration = pulseIn(pinEcho, HIGH);
		 
		 //Calculate the distance (in cm) based on the speed of sound.
		 distance = duration/58.2;
		 Serial.println(distance);
	};
	
	long GetDistance() { return distance; };
	
	virtual void GetKeyValues(KeyValue *keyValues, short &size) override
	{
		keyValues[size] = KeyValue("Расстояние", String(distance)); size++;
	};
	
};