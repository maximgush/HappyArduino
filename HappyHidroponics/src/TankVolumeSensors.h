
#include <interfaces/ITankVolumeSensor.h>

// Интерфейс сенсора измеряющего объём жидкости в баке
class TankVolumeSensorUsingUltrasonicDistanceSensor : public ITankVolumeSensor, public Component
{
public:
	// ITankVolumeSensor
	virtual float GetValue() const override { return currentTankVolume; };
	
	// IComponent
	virtual void OnFrame() override;
	
private:
	float currentTankVolume;
	UltrasonicDistanceSensor* ultrasonicDistanceSensor;
	
	// Таблица устанавливающая соответствие между уровнем жидкости в баке
	// (по значению сенсора) и объёмом жидкости
	LinearSpline* tableSensorValueCurrentCapacity = nullptr;
}

// Сенсор измеряющий объём бака на основе заполнения другого бака
class TankVolumeSensorUsingFillingConnectedTank : public ITankVolumeSensor
{
public:
	// ITankVolumeSensor
	virtual float GetValue() const override;

	// IComponent
	virtual void OnFrame() override;
	
private:
	// Соединённый бак из которого жидкость перетекает в этот
	ITank * connectedTank;	
	
	// Текущий объём жидкости в системе сообщающихся сосудов
	// вычисляемый как максимальное значение жидкости в родительском баке
	// за определённый интервал
	float currentVolumeInSystemConnectedTanks = 0;
}

void TankVolumeSensorUsingUltrasonicDistanceSensor::OnFrame() override
{
	short sensorValue = ultrasonicDistanceSensor->GetValue();

	// Проверяем, что значения сенсора не выходят за таблицу
	if( tableSensorValueCurrentCapacity.CheckXLimits( sensorValue ) )
	{
		// Некорректное значение датчика или таблица
		return;
	}

	// Вычисляем текущее значение по таблице
	currentTankVolume = tableSensorValueCurrentCapacity.GetValue( sensorValue );
}

float TankVolumeSensorUsingFillingConnectedTank::GetValue() const
{
	return currentVolumeInSystemConnectedTanks - connectedTank->GetCurrentCapacity();
};

void TankVolumeSensorUsingFillingConnectedTank::OnFrame()
{
	// Вычисляем текущий объём жидкости в системе сообщающихся сосудов
	// вычисляемый как максимальное значение жидкости в родительском баке
	// за определённый интервал

	// TODO
	float currentVolumeInConnectedTank = connectedTank->GetCurrentCapacity();
}