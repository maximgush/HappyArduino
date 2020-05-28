#pragma once

#include "interfaces/IRTC.h"
#include "Component.h"

#include <RTClib.h>

class RTCComponent : public IRTC, public Component
{
public:
	RTCComponent( const char* _name );

	// Component
	virtual void Init() override;
	virtual void OnFrame() override {};
	virtual void GetKeyValues( KeyValue *keyValues, short &size ) override;
	
	// Метод для установки текущего времени и даты в сенсор
	// Текущая время и даты берутся системные и хардкодятся при компиляции программы
	// Необходимо однократно вызвать в методе loop()
	// Лучше использовать плату под которую быстро компилируется и загружается проишивка
	// (например Ардуино UNO/Nano/...) иначе будет значительное отставание времени сенсора
	void SetCurrentDateAndTime();

public:
	RTC_DS3231 rtc;
};