// Интерфейс объекта, который предоставляет данные о реальном времени
#include <DateTime.h>

class IRTC {
public:
	// Возвращает текущие дату и время
	virtual CDateTime GetCurrentTime() const = 0;
};