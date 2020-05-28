#pragma once

#include "LM35TempSensorComponent.h"

LM35TempSensorComponent::LM35TempSensorComponent( const char* _name, short _pin )
	: Component( _name )
	, pin( _pin )
	, temperature( -273 )
{
}

void LM35TempSensorComponent::Init()
{
};

void LM35TempSensorComponent::OnFrame()
{
	analogValue = analogRead( pin );
	temperature = ( 125 * analogValue ) >> 8;
};

void LM35TempSensorComponent::GetKeyValues( KeyValue *keyValues, short &size ) const
{
	keyValues[size] = KeyValue( "Аналоговое значение", String( analogValue, DEC ) ); size++;
	keyValues[size] = KeyValue( "Температура", String( temperature, DEC ) + " °С" ); size++;
};