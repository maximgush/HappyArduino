// ��������� �������, ������� ������������� ������ � �������� �������
#include <DateTime.h>

class IRTC {
public:
	// ���������� ������� ���� � �����
	virtual CDateTime GetCurrentTime() const = 0;
};