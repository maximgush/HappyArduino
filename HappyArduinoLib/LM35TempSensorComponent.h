#pragma once

#include "interfaces/ITemperatureSensor.h"
#include "Component.h"

class LM35TempSensorComponent : public ITemperatureSensor, public Component
{
public:
	LM35TempSensorComponent( const char* _name, short _pin );

	// Component
	virtual void Init() override;
	virtual void OnFrame() override;
	virtual void GetKeyValues( KeyValue *keyValues, short &size ) const override;


	virtual float GetTemperature() const override { return temperature; }

private:
	short pin;
	short analogValue;
	float temperature;
};