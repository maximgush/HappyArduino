// Интерфейс объекта, который можно включить или выключить
class IOnOff
{
public:
	virtual void On() = 0;
	virtual void Off() = 0;	
}