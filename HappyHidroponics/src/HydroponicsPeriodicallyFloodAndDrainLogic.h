class HydroponicsPeriodicallyFloodAndDrainLogic
{
public:
	interface IChangeStateSubscriber
	{
		virtual OnChangeState( State newState ) = 0;
	};
	
  enum class State
  {	
    Flooding,	// Затопление	
    Draining,	// Осушение	
    Waiting,	// Ожидание следующего затопления
    Stopped	// Система остановлена
  };
  
	HydroponicsPeriodicallyFloodAndDrainLogic(IRTC* _rtc, ITank* _tank, IOnOff* _pump)
		: tank(_tank)
		, rtc(_rtc)
		, timeStartLastFloodDrainCycle(_rtc->GetCurrentTime())
		, state(Stopped)
		, pump(_pump)
	{		
	}
	
	virtual void OnFrame() override
	{
		switch(state)
		{
			case Flooding:
				if (tank->GetCurrentFilling() >= tankFullLevel)
					changeStateTo(State::Draining);
				break;
				
			case Draining:
				if (tank->GetCurrentFilling() <= tankEmptyLevel)
					changeStateTo(State::Waiting);
				break;
				
			case Waiting:
				rtc = GetCurrentTime();
				// Вычисляем время прошедшее с последнего полива
				short delta = rtc->GetCurrentTime() - timeStartLastFloodDrainCycle;
				
				if (delta >= cycleTimeOnCurrentTimeOfDay)
					changeStateTo(State::Draining);				
				break;

			case Stopped:
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
		changeStateTo(State::Flooding);
	}

	// Останавливает работу
	void Stop()
	{
		changeStateTo(State::Stopped);
	}
  
private:
	// Интерфейс предоставляющий данные о реальном времени
	IRTC *rtc;
	
	// Интерфейс предоставляющий информацию об уровне жидкости в заполняемом баке 
	ITank * tank;
	
	// Включатель/выключатель насоса
	IOnOff * pump;
  
	// Текущее состояние системы
	HydroponicsPeriodicallyFloodAndDrainState state = State::Waiting;
	
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
	
	List<IChangeStateSubscriber*> onChangeStateubscribers;
		
	void changeStateTo(State newState)
	{
		if (state == newState)
			return;
		
		switch(newState)
		{
			case State::Flooding:
				timeStartLastFloodDrainCycle = rtc->GetCurrentTime();
				pump->On();		
				break;
				
			case State::Draining:
				pump->Off();				
				break;
				
			case State::Waiting:
				pump->Off();
				cycleTimeOnCurrentTimeOfDay = tableCycleTimeDependingOnTimeOfDay.GetValue(rtc->GetCurrentTime());			
				break;
				
			default:
				//assert();
				pump->Off();
				break;
		}
		
		// TODO: оповещаем всех подписчиков о смене состояния
		//foreach (IChangeStateSubscriber* subscriber : onChangeStateToSubscribers)
		{
		//	subscriber->OnChangeState(newState);
		}	
	}
}