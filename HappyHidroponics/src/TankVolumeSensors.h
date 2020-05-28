
#include <interfaces/ITankVolumeSensor.h>

// ��������� ������� ����������� ����� �������� � ����
class TankVolumeSensorUsingUltrasonicDistanceSensor : public ITankVolumeSensor, public Component
{
public:
	// ITankVolumeSensor
	virtual float GetValue() const override { return currentTankVolume; };
	
	// IComponent
	virtual void OnFrame() override;
	
private:
	float currentTankVolume;
	UltrasonicDistanceSensor* ultrasonicDistanceSensor;
	
	// ������� ��������������� ������������ ����� ������� �������� � ����
	// (�� �������� �������) � ������� ��������
	LinearSpline* tableSensorValueCurrentCapacity = nullptr;
}

// ������ ���������� ����� ���� �� ������ ���������� ������� ����
class TankVolumeSensorUsingFillingConnectedTank : public ITankVolumeSensor
{
public:
	// ITankVolumeSensor
	virtual float GetValue() const override;

	// IComponent
	virtual void OnFrame() override;
	
private:
	// ���������� ��� �� �������� �������� ���������� � ����
	ITank * connectedTank;	
	
	// ������� ����� �������� � ������� ������������ �������
	// ����������� ��� ������������ �������� �������� � ������������ ����
	// �� ����������� ��������
	float currentVolumeInSystemConnectedTanks = 0;
}

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