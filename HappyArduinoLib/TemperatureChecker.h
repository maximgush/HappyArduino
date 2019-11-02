class ITemperatureSensor
{
public:
	virtual float GetTemperature() = 0;
};

class TemperatureChecker
{
public:
	TemperatureChecker(ITemperatureSensor* _temperatureSensor, float checkedValue,  )
		: temperatureSensor( _temperatureSensor )
	{

	}

	virtual void Check() override
	{
		if( )
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