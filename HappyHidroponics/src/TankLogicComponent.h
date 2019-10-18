#include <ITank.h>

// Интерфейс бака с жидкостью заполнение которого зависит от текущего заполнения другого бака
class TankLogicComponent : public ITank
{
public:
	TankLogicComponent( ITankVolumeSensor* _tankVolumeSensor) :
		tankVolumeSensor(_tankVolumeSensor)
	{
	}
	
	// ITank
	virtual void SetMaxCapacity(float _maxCapacity) override { maxCapacity = _maxCapacity; };	
	virtual float GetMaxCapacity() override { return maxCapacity; }	
	virtual float GetCurrentCapacity() override
	{
		return clamp(tankVolumeSensor->GetValue(), 0, maxCapacity);
	};
	
private:	
	// Максимальная ёмкость бака в литрах
	float maxCapacity = 1.0;
	
	// Сенсор измеряющий объём жидкости в баке
	ITankVolumeSensor* tankVolumeSensor;
}