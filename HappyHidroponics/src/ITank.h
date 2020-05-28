// Интерфейс бака с жидкостью
interface ITank
{
	// Возвращает максимальную вместительность бака в литрах
	virtual float GetMaxCapacity() const = 0;
	
	// Устанавливает текущий максимальный объём жидкости в баке в литрах
	virtual void SetMaxCapacity(float _maxCapacity) = 0;
	
	// Возвращает текущий объём жидкости в баке в литрах
	virtual float GetCurrentCapacity() const = 0;	
	
	// Заполнение бака в %
	virtual float GetCurrentFilling() const { return GetCurrentCapacity() / GetMaxCapacity(); };
}

// Интерфейс сенсора измеряющего объём жидкости в баке
interface ITankVolumeSensor
{
	// Возвращает объём жидкости в литрах
	virtual float GetValue() = 0;
}