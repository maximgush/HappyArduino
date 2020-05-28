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
	virtual void GetKeyValues( KeyValue *keyValues, short &size ) const override;
	
	// IOnOff
	virtual bool IsOn() const override;
	virtual void On() override;
	virtual void Off() override;

private:
	bool isOn;	// Текущее состояние реле
	int pin;	// номер пина к которому подключен управлящий реле сигнал
};

RelayComponent::RelayComponent( const char* _name, int _pin, bool _isOn )
	: Component( _name )
	, pin( _pin )
	, isOn( _isOn )
{
}

void RelayComponent::Init()
{
	pinMode( pin, OUTPUT );
	digitalWrite( pin, LOW );
}

void RelayComponent::RelayComponent::OnFrame()
{
	digitalWrite( pin, isOn ? HIGH : LOW );
};

void RelayComponent::GetKeyValues( KeyValue *keyValues, short &size ) const
{
	keyValues[size] = KeyValue( "Включено", String( IsOn() ) ); size++;
};

bool RelayComponent::IsOn() const
{
	return isOn;
};

void RelayComponent::On()
{
	isOn = true;
	digitalWrite( pin, HIGH );
};

void RelayComponent::Off()
{
	isOn = false;
	digitalWrite( pin, LOW );
};