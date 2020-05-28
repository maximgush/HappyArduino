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
		// TODO ���������, ��� ����� ����������
		if (false)
		{
			// TODO ������ ��������� �������: ������������ ��������
		}
	}
private:
	ITemperatureSensor* rtc;
}