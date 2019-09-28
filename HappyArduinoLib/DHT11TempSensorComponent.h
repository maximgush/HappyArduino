#pragma once

#include "Component.h"
#include "DHT.h"

enum eDHTType
{
	edtDHT11,
	edtDHT22,
	edtDHT21
};

class DHT11TempSensorComponent : public Component
{
private:
	short pin;
	float humidity;
	float temperature;

	DHT dht;
public:
	DHT11TempSensorComponent (const char* _name, short _pin, eDHTType dhtType)
		: Component(_name)
		, pin(_pin)
		, dht(pin, dhtType)
		, temperature(-273)
		, humidity(-1)
	{				
	}

	virtual void Init() override
	{
		dht.begin();
	}
	
	virtual void OnFrame() override
	{
		humidity = dht.readHumidity();
  		temperature = dht.readTemperature();
	};
	
	virtual void GetKeyValues(KeyValue *keyValues, short &size) override
	{
		keyValues[size] = KeyValue("Температура", String(temperature, DEC) + " °С"); size++;
		keyValues[size] = KeyValue("Влажность", String(temperature, DEC) + " %"); size++;
		keyValues[size] = KeyValue("pin", String(pin, DEC)); size++;
	};
	
	float GetTemperature()
	{
		return temperature;
	}

	float GetHumidity()
	{
		return humidity;
	}
};