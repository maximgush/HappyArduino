#pragma once

#include "interfaces/IOnOff.h"
#include "Component.h"

class RelayComponent : public IOnOff, public Component
{
public:
	RelayComponent( const char* _name, int _pin, bool _isOn = false );

	// Component
	virtual void Init() override;
	virtual void OnFrame() override;
	virtual void GetKeyValues( KeyValue *keyValues, short &size ) override;
	
	// IOnOff
	virtual bool IsOn() const override;
	virtual void On() override;
	virtual void Off() override;

private:
	bool isOn;	// Текущее состояние реле
	int pin;	// номер пина к которому подключен управлящий реле сигнал
};