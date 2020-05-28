
#include <TankVolumeSensors.h>

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