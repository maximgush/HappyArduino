// Интерфейс объекта, который предоставляет данные о реальном времени
class IRTC {
public:
	struct DateTime
	{

	};

	// Возвращает текущие дату и время
	virtual DateTime GetCurrentTime() const = 0;
};