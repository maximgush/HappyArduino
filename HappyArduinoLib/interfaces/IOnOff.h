// ��������� �������, ������� ����� �������� ��� ���������
class IOnOff
{
public:
	virtual bool IsOn() const = 0;
	virtual void On() = 0;
	virtual void Off() = 0;	
}