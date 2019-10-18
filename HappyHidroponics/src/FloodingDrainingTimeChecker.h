// ����� ��������������, ��� ������ � ����� ���������� �� ����������� �����
class FloodingDrainingTimeChecker : public ICheckable,
									public HydroponicsPeriodicallyFloodAndDrainLogic::IChangeStateToSubscriber
{	
public:	
	// HydroponicsPeriodicallyFloodAndDrainLogic::IChangeStateToSubscriber
	virtual OnChangeStateTo(HydroponicsPeriodicallyFloodAndDrainLogic::State newState) override
	{
		if (newState == flooding)
			timeStartFlood = rtc->GetCurrentTime();
		else
			timeStartDrain = rtc->GetCurrentTime();	
	}
	virtual void Check() override
	{        
		DateTime curTime = rtc->GetCurrentTime();
		
		int deltaTimeFlood = curTime - timeStartFlood;
		if ( deltaTime > floodStandardTime )
		{
			// ���������� �� ���������� (��� ���������� ��������)
		}
			
		int deltaTimeDrain = curTime - timeStartDrain;
		if ( deltaTimeDrain > drainStandardTime )
		{
			// �������� �� ���������� (��� ���������� ��������)
		}			
	}
	
private:
	// ������ ��������������� ������ � �������� �������
	IRTC* rtc;
	
	// ����������� ����� �� ������� ������ ��������� ���������� ����
	float floodStandardTime = 30;
	
	// ����������� ����� �� ������� ������ ��������� �������� ����
	float drainStandardTime = 500;
	
	// ����� ������ ���������� ����
	DateTime timeStartFlood;
	
	// ����� ������ �������� ����
	DateTime timeStartDrain;
}

// ����� ���������� ���������� � �������/�������
class FloodingDrainingTimeChecker : public HydroponicsPeriodicallyFloodAndDrainLogic::IChangeStateToSubscriber
{
	// HydroponicsPeriodicallyFloodAndDrainLogic::IChangeStateToSubscriber
	virtual OnChangeStateTo(HydroponicsPeriodicallyFloodAndDrainLogic::State newState) override
	{
		// TODO:
		// ���������� � ������[10] ����� ��������� � ������� ����� ��� ����������� � ����
	}
}