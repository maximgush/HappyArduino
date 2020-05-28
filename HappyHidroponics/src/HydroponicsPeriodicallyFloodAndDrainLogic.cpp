#include <HydroponicsPeriodicallyFloodAndDrainLogic.h>

HydroponicsPeriodicallyFloodAndDrainLogic::HydroponicsPeriodicallyFloodAndDrainLogic( IRTC* _rtc, ITank* _tank, IOnOff* _pump )
	: tank( _tank )
	, rtc( _rtc )
	, timeStartLastFloodDrainCycle( rtc->GetCurrentTime() )
	, state( Stopped )
	, pump( _pump )
{
}

void HydroponicsPeriodicallyFloodAndDrainLogic::OnFrame()
{
	switch( state )
	{
	case Flooding:
		if( tank->GetCurrentFilling() >= tankFullLevel )
			changeStateTo( State::Draining );
		break;

	case Draining:
		if( tank->GetCurrentFilling() <= tankEmptyLevel )
			changeStateTo( State::Waiting );
		break;

	case Waiting:
		rtc = GetCurrentTime();
		// Вычисляем время прошедшее с последнего полива
		short delta = rtc->GetCurrentTime() - timeStartLastFloodDrainCycle;

		if( delta >= cycleTimeOnCurrentTimeOfDay )
			changeStateTo( State::Draining );
		break;

	case Stopped:
		return;
		break;

	default:
		//assert();
		break;
	}
}

// Функция для переключения текущего состояния
void HydroponicsPeriodicallyFloodAndDrainLogic::changeStateTo( State newState )
{
	if( state == newState )
		return;

	switch( newState )
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
		cycleTimeOnCurrentTimeOfDay = tableCycleTimeDependingOnTimeOfDay.GetValue( rtc->GetCurrentTime() );
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