//  ласс контролирующий, что прилив и отлив происход€т за нормативное врем€
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
			// «атопление не происходит (или происходит медленно)
		}
			
		int deltaTimeDrain = curTime - timeStartDrain;
		if ( deltaTimeDrain > drainStandardTime )
		{
			// ќсушение не происходит (или происходит медленно)
		}			
	}
	
private:
	// ќбъект предоставл€ющий данные о реальном времени
	IRTC* rtc;
	
	// Ќормативное врем€ за которое должно произойти заполнение бака
	float floodStandardTime = 30;
	
	// Ќормативное врем€ за которое должно произойти осушение бака
	float drainStandardTime = 500;
	
	// ¬рем€ начала затоплени€ бака
	DateTime timeStartFlood;
	
	// ¬рем€ начала осушени€ бака
	DateTime timeStartDrain;
}

//  ласс собирающий статистику о поливах/отливах
class FloodingDrainingTimeChecker : public HydroponicsPeriodicallyFloodAndDrainLogic::IChangeStateToSubscriber
{
	// HydroponicsPeriodicallyFloodAndDrainLogic::IChangeStateToSubscriber
	virtual OnChangeStateTo(HydroponicsPeriodicallyFloodAndDrainLogic::State newState) override
	{
		// TODO:
		// «апоминаем в массив[10] новое состо€ние и текущее врем€ дл€ отображени€ в логе
	}
}