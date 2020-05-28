#include "interfaces/ITemperatureSensor.h"

class TemperatureChecker
{
public:
	TemperatureChecker(ITemperatureSensor* _temperatureSensor, float checkedValue )
		: temperatureSensor( _temperatureSensor )
	{

	}

	virtual void Check() override
	{
		if( temperature > checkedValue )
		DateTime dateTime = rtc->GetCurrentTime();
		// TODO проверяем, что время адекватное
		if (false)
		{
			// TODO Датчик реального времени: некорректное значение
		}
	}
private:
	ITemperatureSensor* rtc;
}