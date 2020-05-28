#include <interfaces/IRTC.h>

class HydroponicsPeriodicallyFloodAndDrainLogic
{
public:
	// ��������� �������
	enum class State
	{
		Flooding, // ����������	
		Draining, // ��������	
		Waiting, // �������� ���������� ����������
		Stopped // ������� �����������
	};

	// ��������� ��� �������� �� ������� ��������� ��������� �������
	interface IChangeStateSubscriber
	{
		virtual OnChangeState( State newState ) = 0;
	};
  
	HydroponicsPeriodicallyFloodAndDrainLogic( IRTC* _rtc, ITank* _tank, IOnOff* _pump );
	
	// IComponent
	virtual void OnFrame() override;
	
	// ������������� ������� �������� � ����, ��� ������� ��� ��������� ���������� (�� 0 �� 1)
	void SetTankFullLevel( float level ) { tankFullLevel = level; }
	
	// ������������� ������� �������� � ����, ��� ������� ��� ��������� ������������ (�� 0 �� 1)
	void SetTankEmptyLevel( float level ) { tankEmptyLevel = level; }

	// ��������� � ������
	void Run() { changeStateTo( State::Flooding ); }

	// ������������� ������
	void Stop() { changeStateTo( State::Stopped ); }

	// TODO
	// �������� ������ ��������/�������

private:
	// ��������� ��������������� ������ � �������� �������
	IRTC* rtc = nullptr;

	// ��������� ��������������� ���������� �� ������ �������� � ����������� ���� 
	ITank* tank = nullptr;
	
	// ����������/����������� ������
	IOnOff* pump = nullptr;
  
	// ������� ��������� �������
	HydroponicsPeriodicallyFloodAndDrainState state = State::Stopped;
	
	// ����� ������ ���������� ����� ������/������
	DateTime timeStartLastFloodDrainCycle;
	
	// ����� ����� � �������� ������/������ ����������� �� ������� 
	unsigned short cycleTimeOnCurrentTimeOfDay = 1500;
	
	// ������� ����������� ����� ����� ������/������ � ����������� �� �������� ������� �����
	LinearSpline tableCycleTimeDependingOnTimeOfDay;
	
	// ������� �������� � ����, ��� ������� ��� ��������� ���������� (�� 0 �� 1)
	float tankFullLevel = 0.9;
	// ������� �������� � ����, ��� ������� ��� ��������� ������������ (�� 0 �� 1)
	float tankEmptyLevel = 0.1;
	
	// ������ ����������� �� ������� ��������� ���������
	List<IChangeStateSubscriber*> onChangeStateubscribers;
		
	void changeStateTo( State newState );
}