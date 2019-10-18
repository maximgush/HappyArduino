

// Интерфейс сенсора измеряющего объём жидкости в баке
class TankVolumeSensorUsingUltrasonicDistanceSensor : public ITankVolumeSensor, public Component
{
public:
	// ITankVolumeSensor
	virtual float GetValue() { return currentTankVolume; };
	
	// IComponent
	virtual void OnFrame() override
	{
		short sensorValue = ultrasonicDistanceSensor->GetValue();
		
		// Проверяем, что значения сенсора не выходят за таблицу
		if (tableSensorValueCurrentCapacity.CheckXLimits(sensorValue))
		{
			// Некорректное значение датчика или таблица
			return;
		}
		
		// Вычисляем текущее значение по таблице
		currentTankVolume = tableSensorValueCurrentCapacity.GetValue(sensorValue);
	}
	
private:
	float currentTankVolume;
	UltrasonicDistanceSensor * ultrasonicDistanceSensor;
	
	// Таблица устанавливающая соответствие между уровнем жидкости в баке
	// (по значению сенсора) и объёмом жидкости
	LinearSpline* tableSensorValueCurrentCapacity = nullptr;
}

// TODO написать описание
class TankVolumeSensorUsingFillingConnectedTank : public ITankVolumeSensor
{
public:
	// ITankVolumeSensor
	virtual float GetValue()
	{
		return currentVolumeInSystemConnectedTanks - connectedTank->GetCurrentCapacity();
	};
	
	virtual void OnFrame override
	{
		// Вычисляем текущий объём жидкости в системе сообщающихся сосудов
		// вычисляемый как максимальное значение жидкости в родительском баке
		// за определённый интервал
		
		// TODO
		float currentVolumeInConnectedTank = connectedTank->GetCurrentCapacity();
	}
	
private:
	// Соединённый бак из которого жидкость перетекает в этот
	ITank * connectedTank;	
	
	// Текущий объём жидкости в системе сообщающихся сосудов
	// вычисляемый как максимальное значение жидкости в родительском баке
	// за определённый интервал
	float currentVolumeInSystemConnectedTanks = 0;
}