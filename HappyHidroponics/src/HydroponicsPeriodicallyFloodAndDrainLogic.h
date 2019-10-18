class HydroponicsPeriodicallyFloodAndDrainLogic
{
public:
	interface IChangeStateSubscriber
	{
		virtual OnChangeStateTo( State newState ) = 0;
	};
	
  enum State
  {	
    hpfdlFlooding,	// Затопление	
    hpfdlDraining,	// Осушение	
    hpfdlWaiting,	// Ожидание следующего затопления
    hpfdlStopped	// Система остановлена
  };
  
	HydroponicsPeriodicallyFloodAndDrainLogic(IRTC* _rtc, ITank* _tank)
		: tank(_tank)
		, rtc(_rtc)
		, timeStartLastFloodDrainCycle(_rtc->GetCurrentTime())
		, state(hpfdStopped)
	{		
	}
	
	virtual void OnFrame() override
	{
		switch(state)
		{
			case hpfdlFlooding:
				if (tank->GetCurrentFilling() >= tankFullLevel)
					ChangeState(hpfdlDraining);
				break;
				
			case hpfdlDraining:
				if (tank->GetCurrentFilling() <= tankEmptyLevel)
					ChangeState(hpfdlWaiting);
				break;
				
			case hpfdlWaiting:
				rtc = GetCurrentTime();
				// Вычисляем время прошедшее с последнего полива
				short delta = rtc->GetCurrentTime() - timeStartLastFloodDrainCycle;
				
				if (delta >= cycleTimeOnCurrentTimeOfDay)
					ChangeState(hpfdlDraining);				
				break;

			case hpfdlStopped:
				return;
				break;
				
			default:
				//assert();
				break;
		}
	}
	
	// Устанавливает уровень жидкости в баке, при котором бак считается заполненым (от 0 до 1)
	void SetTankFullLevel(float level)
	{
		tankFullLevel = level;
	}
	
	// Устанавливает уровень жидкости в баке, при котором бак считается опустошённым (от 0 до 1)
	void SetTankEmptyLevel(float level)
	{
		tankEmptyLevel = level;
	}	

	// Запускает в работу
	void Run()
	{
		ChangeStateTo(hpfdlFlooding);
	}

	// Останавливает работу
	void Stop()
	{
		ChangeStateTo(hpfdlStopped);
	}
  
private:
	// Интерфейс предоставляющий данные о реальном времени
	IRTC *rtc;
	
	// Интерфейс предоставляющий информацию об уровне жидкости в заполняемом баке 
	ITank * tank;
	
	// Включатель/выключатель насоса
	IOnOff * pump;
  
	// Текущее состояние системы
	HydroponicsPeriodicallyFloodAndDrainState state = hpfdlWaiting;
	
	// Время начала последнего цикла полива/отлива
	DateTime timeStartLastFloodDrainCycle;
	
	// Время цикла в секундах полива/отлива вычисленное по таблице 
	unsigned short cycleTimeOnCurrentTimeOfDay;
	
	// Таблица описывающая время цикла полива/отлива в зависимости от текущего времени суток
	LinearSpline tableCycleTimeDependingOnTimeOfDay;
	
	// Уровень жидкости в баке, при котором бак считается заполненым (от 0 до 1)
	float tankFullLevel = 0.9;
	// Уровень жидкости в баке, при котором бак считается опустошённым (от 0 до 1)
	float tankEmptyLevel = 0.1;
	
	List<IChangeStateSubscriber*> changeStateToSubscribers;
		
	void ChangeState(State newState)
	{
		if (state == newState)
			return;
		
		switch(newState)
		{
			case hpfdlFlooding:
				timeStartLastFloodDrainCycle = rtc->GetCurrentTime();
				pump->On();		
				break;
				
			case hpfdlDraining:
				pump->Off();				
				break;
				
			case hpfdlWaiting:
				pump->Off();
				cycleTimeOnCurrentTimeOfDay = tableCycleTimeDependingOnTimeOfDay.GetValue(rtc->GetCurrentTime());			
				break;
				
			default:
				//assert();
				pump->Off();
				break;
		}
		
		// TODO: оповещаем всех подписчиков о смене состояния
		//foreach (IChangeStateSubscriber* subscriber : changeStateToSubscribers)
		{
		//	subscriber->OnChangeStateTo(newState);
		}	
	}
}