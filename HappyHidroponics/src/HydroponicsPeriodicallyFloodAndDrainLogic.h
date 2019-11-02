class HydroponicsPeriodicallyFloodAndDrainLogic
{
public:
	interface IChangeStateSubscriber
	{
		virtual OnChangeState( State newState ) = 0;
	};
	
  enum class State
  {	
    Flooding,	// ����������	
    Draining,	// ��������	
    Waiting,	// �������� ���������� ����������
    Stopped	// ������� �����������
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
				// ��������� ����� ��������� � ���������� ������
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
	
	// ������������� ������� �������� � ����, ��� ������� ��� ��������� ���������� (�� 0 �� 1)
	void SetTankFullLevel(float level)
	{
		tankFullLevel = level;
	}
	
	// ������������� ������� �������� � ����, ��� ������� ��� ��������� ������������ (�� 0 �� 1)
	void SetTankEmptyLevel(float level)
	{
		tankEmptyLevel = level;
	}	

	// ��������� � ������
	void Run()
	{
		changeStateTo(State::Flooding);
	}

	// ������������� ������
	void Stop()
	{
		changeStateTo(State::Stopped);
	}
  
private:
	// ��������� ��������������� ������ � �������� �������
	IRTC *rtc;
	
	// ��������� ��������������� ���������� �� ������ �������� � ����������� ���� 
	ITank * tank;
	
	// ����������/����������� ������
	IOnOff * pump;
  
	// ������� ��������� �������
	HydroponicsPeriodicallyFloodAndDrainState state = State::Waiting;
	
	// ����� ������ ���������� ����� ������/������
	DateTime timeStartLastFloodDrainCycle;
	
	// ����� ����� � �������� ������/������ ����������� �� ������� 
	unsigned short cycleTimeOnCurrentTimeOfDay;
	
	// ������� ����������� ����� ����� ������/������ � ����������� �� �������� ������� �����
	LinearSpline tableCycleTimeDependingOnTimeOfDay;
	
	// ������� �������� � ����, ��� ������� ��� ��������� ���������� (�� 0 �� 1)
	float tankFullLevel = 0.9;
	// ������� �������� � ����, ��� ������� ��� ��������� ������������ (�� 0 �� 1)
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
		
		// TODO: ��������� ���� ����������� � ����� ���������
		//foreach (IChangeStateSubscriber* subscriber : onChangeStateToSubscribers)
		{
		//	subscriber->OnChangeState(newState);
		}	
	}
}