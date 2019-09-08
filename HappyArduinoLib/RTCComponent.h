#pragma once

#include "Component.h"

#include <RTClib.h>
#include <Wire.h>

class RTCComponent : public Component
{
public:
	RTC_DS3231 rtc;
public:
	RTCComponent(const char* _name)
		: Component(_name) {}
	virtual void Init()
	{
		Wire.begin(); 
		rtc.begin();
	}
	virtual void OnFrame() {};
	
	virtual void GetKeyValues(KeyValue *keyValues, short &size) override
	{
		DateTime nowTime = rtc.now();
		char timeStr[10];
		sprintf(timeStr, "%02d:%02d:%02d", nowTime.hour(), nowTime.minute(), nowTime.second());
		keyValues[size] = KeyValue("Текущее время", timeStr); size++;
		sprintf(timeStr, "%02d:%02d:%4d", nowTime.day(), nowTime.month(), nowTime.year());
		keyValues[size] = KeyValue("Текущее дата", timeStr); size++;
		keyValues[size] = KeyValue("Температура", String(rtc.getTemperature())); size++;
	};
	
	// Метод для установки текущего времени и даты в сенсор
	// Текущая время и даты берутся системные и хардкодятся при компиляции программы
	// Необходимо однократно вызвать в методе loop()
	// Лучше использовать плату под которую быстро компилируется и загружается проишивка
	// (например Ардуино UNO/Nano/...) иначе будет значительное отставание времени сенсора
	void SetCurrentDateAndTime()
	{
		rtc.adjust(DateTime(F(__DATE__),F(__TIME__)));
	}
};