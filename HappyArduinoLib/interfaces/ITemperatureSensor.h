#pragma once

// ��������� �������, ������� ������������� ������ � �����������
class ITemperatureSensor
{
public:
	// ���������� �������� ����������� � �������� �������
	virtual float GetTemperature() const = 0;
};