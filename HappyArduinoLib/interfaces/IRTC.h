// ��������� �������, ������� ������������� ������ � �������� �������
class IRTC {
public:
	struct DateTime
	{

	};

	// ���������� ������� ���� � �����
	virtual DateTime GetCurrentTime() const = 0;
};