class RTCChecker
{
public:
	RTCChecker(IRTC* _rtc)
		: rtc(_rtc)
	{

	}

	virtual void Check() override
	{
		DateTime dateTime = rtc->GetCurrentTime();
		// TODO ���������, ��� ����� ����������
		if (false)
		{
			// TODO ������ ��������� �������: ������������ ��������
		}
	}
private:
	IRTC* rtc;
}