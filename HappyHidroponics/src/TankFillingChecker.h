#include <ICheckable.h>

class TankFillingChecker : public ICheckable
{
	
private:
	// Бак для которого делаем проверки
	ITank* tank;
	
	// Уровень заполнения бака при опускании ниже которого выдастся предупреждение
	float minValue = 0.3;
	
	// Уровень заполнения бака при привышении которого выдастся предупреждение
	float maxValue = 1.0;

public:	
	// ICheckable
	virtual void Check() override
	{        
		float currentFilling = tank->GetCurrentFilling();

		else if ( currentFilling < minValue )
		{
			// Низкий уровень питательного раствора
		}
		else if ( currentFilling > maxValue )
		{
			// Высокий уровень питательного раствора
		}
	}
	
	void SetMinValue(float value)
	{
		minValue = value;
	}
	
	void SetMaxValue(float value)
	{
		maxValue = value;
	}
	
}