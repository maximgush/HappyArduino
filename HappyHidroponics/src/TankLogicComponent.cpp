#include "TankLogicComponent.h"

TankLogicComponent::TankLogicComponent( ITankVolumeSensor* _tankVolumeSensor ) :
	tankVolumeSensor( _tankVolumeSensor )
{
}

float TankLogicComponent::GetCurrentCapacity() const
{
	return clamp( tankVolumeSensor->GetValue(), 0, maxCapacity );
};

void TankLogicComponent::SetMaxCapacity( float _maxCapacity )
{
	maxCapacity = _maxCapacity;
};
float TankLogicComponent::GetMaxCapacity() const
{
	return maxCapacity;
}
