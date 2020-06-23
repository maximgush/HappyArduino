#include <RTCComponent.h>
#include <RTClib.h>
#include <Wire.h>


RTCComponent::RTCComponent( const char* _name )
	: Component( _name )
{
}

void RTCComponent::Init()
{
	Wire.begin();
	rtc.begin();
}

void RTCComponent::OnFrame()
{
};

void RTCComponent::GetKeyValues( KeyValue *keyValues, short &size ) const
{
	DateTime nowTime = rtc.now();
	char timeStr[10];
	sprintf( timeStr, "%02d:%02d:%02d", nowTime.hour(), nowTime.minute(), nowTime.second() );
	keyValues[size] = KeyValue( "Текущее время", timeStr ); size++;
	sprintf( timeStr, "%02d:%02d:%4d", nowTime.day(), nowTime.month(), nowTime.year() );
	keyValues[size] = KeyValue( "Текущее дата", timeStr ); size++;
	keyValues[size] = KeyValue( "Температура", String( rtc.getTemperature() ) ); size++;
};

CDateTime RTCComponent::GetCurrentTime() const
{
	DateTime nowTime = rtc.now();
	return CDateTime(nowTime.year(), nowTime.month(), nowTime.day(), nowTime.hour(), nowTime.minute(), nowTime.second());
}

void RTCComponent::SetCurrentDateAndTime()
{
	rtc.adjust( DateTime( F( __DATE__ ), F( __TIME__ ) ) );
}