#include <interfaces/IRTC.h>

class HydroponicsPeriodicallyFloodAndDrainLogic
{
public:
	// Состояние системы
	enum class State
	{
		Flooding, // Затопление	
		Draining, // Осушение	
		Waiting, // Ожидание следующего затопления
		Stopped // Система остановлена
	};

	// Интерфейс для подписки на события изменения состояния системы
	interface IChangeStateSubscriber
	{
		virtual OnChangeState( State newState ) = 0;
	};
  
	HydroponicsPeriodicallyFloodAndDrainLogic( IRTC* _rtc, ITank* _tank, IOnOff* _pump );
	
	// IComponent
	virtual void OnFrame() override;
	
	// Устанавливает уровень жидкости в баке, при котором бак считается заполненым (от 0 до 1)
	void SetTankFullLevel( float level ) { tankFullLevel = level; }
	
	// Устанавливает уровень жидкости в баке, при котором бак считается опустошённым (от 0 до 1)
	void SetTankEmptyLevel( float level ) { tankEmptyLevel = level; }

	// Запускает в работу
	void Run() { changeStateTo( State::Flooding ); }

	// Останавливает работу
	void Stop() { changeStateTo( State::Stopped ); }

	// TODO
	// Добавить методы подписки/отписки

private:
	// Интерфейс предоставляющий данные о реальном времени
	IRTC* rtc = nullptr;

	// Интерфейс предоставляющий информацию об уровне жидкости в заполняемом баке 
	ITank* tank = nullptr;
	
	// Включатель/выключатель насоса
	IOnOff* pump = nullptr;
  
	// Текущее состояние системы
	HydroponicsPeriodicallyFloodAndDrainState state = State::Stopped;
	
	// Время начала последнего цикла полива/отлива
	DateTime timeStartLastFloodDrainCycle;
	
	// Время цикла в секундах полива/отлива вычисленное по таблице 
	unsigned short cycleTimeOnCurrentTimeOfDay = 1500;
	
	// Таблица описывающая время цикла полива/отлива в зависимости от текущего времени суток
	LinearSpline tableCycleTimeDependingOnTimeOfDay;
	
	// Уровень жидкости в баке, при котором бак считается заполненым (от 0 до 1)
	float tankFullLevel = 0.9;
	// Уровень жидкости в баке, при котором бак считается опустошённым (от 0 до 1)
	float tankEmptyLevel = 0.1;
	
	// Список подписчиков на события изменения состояния
	List<IChangeStateSubscriber*> onChangeStateubscribers;
		
	void changeStateTo( State newState );
}