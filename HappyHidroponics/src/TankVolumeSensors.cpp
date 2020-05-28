
#include <TankVolumeSensors.h>

void TankVolumeSensorUsingUltrasonicDistanceSensor::OnFrame() override
{
	short sensorValue = ultrasonicDistanceSensor->GetValue();

	// ���������, ��� �������� ������� �� ������� �� �������
	if( tableSensorValueCurrentCapacity.CheckXLimits( sensorValue ) )
	{
		// ������������ �������� ������� ��� �������
		return;
	}

	// ��������� ������� �������� �� �������
	currentTankVolume = tableSensorValueCurrentCapacity.GetValue( sensorValue );
}

float TankVolumeSensorUsingFillingConnectedTank::GetValue() const
{
	return currentVolumeInSystemConnectedTanks - connectedTank->GetCurrentCapacity();
};

void TankVolumeSensorUsingFillingConnectedTank::OnFrame()
{
	// ��������� ������� ����� �������� � ������� ������������ �������
	// ����������� ��� ������������ �������� �������� � ������������ ����
	// �� ����������� ��������

	// TODO
	float currentVolumeInConnectedTank = connectedTank->GetCurrentCapacity();
}