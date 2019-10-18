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
		// TODO проверяем, что время адекватное
		if (false)
		{
			// TODO Датчик реального времени: некорректное значение
		}
	}
private:
	IRTC* rtc;
}