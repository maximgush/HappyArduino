class HydroponicsPeriodicallyFloodAndDrainLogic
{
public:
	interface IChangeStateSubscriber
	{
		virtual OnChangeStateTo( State newState ) = 0;
	};
	
  enum State
  {	
    hpfdlFlooding,	// ����������	
    hpfdlDraining,	// ��������	
    hpfdlWaiting,	// �������� ���������� ����������
    hpfdlStopped	// ������� �����������
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
				// ��������� ����� ��������� � ���������� ������
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
		ChangeStateTo(hpfdlFlooding);
	}

	// ������������� ������
	void Stop()
	{
		ChangeStateTo(hpfdlStopped);
	}
  
private:
	// ��������� ��������������� ������ � �������� �������
	IRTC *rtc;
	
	// ��������� ��������������� ���������� �� ������ �������� � ����������� ���� 
	ITank * tank;
	
	// ����������/����������� ������
	IOnOff * pump;
  
	// ������� ��������� �������
	HydroponicsPeriodicallyFloodAndDrainState state = hpfdlWaiting;
	
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
		
		// TODO: ��������� ���� ����������� � ����� ���������
		//foreach (IChangeStateSubscriber* subscriber : changeStateToSubscribers)
		{
		//	subscriber->OnChangeStateTo(newState);
		}	
	}
}