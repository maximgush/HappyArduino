#pragma once

// Интерфейс объекта, который предоставляет данные о температуре
class ITemperatureSensor
{
public:
	// Возвращает значение температуры в градусах Цельсия
	virtual float GetTemperature() const = 0;
};