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
		// TODO ���������, ��� ����� ����������
		if (false)
		{
			// TODO ������ ��������� �������: ������������ ��������
		}
	}
private:
	ITemperatureSensor* rtc;
}