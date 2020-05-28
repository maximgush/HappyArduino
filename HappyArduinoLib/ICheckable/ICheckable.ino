class ICheckable
{
public:
    virtual void Check() = 0;
    virtual String GetDescription() = 0;
};


class TankLogicComponent : public IComponent, public ICheckable
{
  // Емкость бака
  short maxVolume;

  // Таблица устанавливающая соответствие между уровнем жидкости в баке
  // (по значению сенсора) и объёмом жидкости
  LinearSpline tableSensorVolume;

  // Текущее заполнение бака % 
  short currentLevel;

  // Уровни заполнения % соответствующие низкому и высокому значению (для предупреждений)
  short lowLevel, highLevel;

public:
  virtual void OnFrame() override
  {
    // Получаем значение от сенсора
    short sensorValue = 10;

    // Проверяем, что значение сенсора адекватное

    // Проверяем, что значения сенсора не выходят за таблицу
    if (LinearSpline.CheckXLimits(sensorValue))
    {
      // Некорректное значение датчика
      return;
    }

    // Вычисляем текущее значение по таблице
    float currentValume = LinearSpline.GetValue(sensorValue);

    currentLevel = currentVolume / maxVolume;
  }

  // Возвращает текущий уровень заполнения бака
  short GetCurrentLevel()
  {
    return currentLevel;
  }

  // Возвращает текущее заполнения бака в литрах
  short GetCurrentLevel()
  {
    return currentLevel * maxVolume;
  }

  virtual void Check() override
  {        
    // Проверяем, что значения сенсора не выходят за таблицу
    if (LinearSpline.CheckXLimits(sensorValue))
    {
      // Некорректное значение датчика
    }
    else if ( currentLevel < levelLow )
    {
       // Низкий уровень питательного раствора
    }
    else if ( currentLevel > levelHigh )
    {
       // Высокий уровень питательного раствора
    }
}

class HydroponicsPeriodicallyFloodAndDrainLogic
{
  enum Status
  {
    Flood,
    Drain,
    Waiting
  }
}

class IncreaseDecreaseLevelInTankChecker
{
  IRTC *rtc;
  
  
  // Должен знать смену состояния полив/отлив и те
  virtual void Check()
  {
    
  }
}
// Уровень раствора не понижается при поливе 
// Уровень раствора не повышается при отливе 
// Датчик реального времени: некорректное значение
 

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:  
}
