#include <ITank.h>

// Бак с жидкостью
class TankLogicComponent : public ITank
{
public:
	TankLogicComponent( ITankVolumeSensor* _tankVolumeSensor );
	
	// ITank
	virtual void SetMaxCapacity( float _maxCapacity ) override;
	virtual float GetMaxCapacity() const override;
	virtual float GetCurrentCapacity() const override;
	
private:	
	// Максимальная ёмкость бака в литрах
	float maxCapacity = 1.0;
	
	// Сенсор измеряющий объём жидкости в баке
	ITankVolumeSensor* tankVolumeSensor;
}