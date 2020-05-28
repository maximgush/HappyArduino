
#include "UltrasonicDistanceSensorComponent.h"

UltrasonicDistanceSensorComponent::UltrasonicDistanceSensorComponent( const char* _name, int _pinTrigger, int _pinEcho )
	: Component( _name )
	, pinTrigger( _pinTrigger )
	, pinEcho( _pinEcho )
	, distance( -1 )
{
}

void UltrasonicDistanceSensorComponent::Init()
{
	pinMode( pinTrigger, OUTPUT );
	pinMode( pinEcho, INPUT );
	digitalWrite( pinTrigger, LOW );
	digitalWrite( pinEcho, LOW );
}

void UltrasonicDistanceSensorComponent::OnFrame()
{
	digitalWrite( pinTrigger, LOW );
	delayMicroseconds( 2 );

	digitalWrite( pinTrigger, HIGH );
	delayMicroseconds( 10 );
	digitalWrite( pinTrigger, LOW );
	long duration = pulseIn( pinEcho, HIGH );

	//Calculate the distance (in cm) based on the speed of sound.
	distance = duration / 58.2;
};

void UltrasonicDistanceSensorComponent::GetKeyValues( KeyValue *keyValues, short &size ) const
{
	keyValues[size] = KeyValue( "Расстояние", String( distance ) ); size++;
};