

// ��������� ������� ����������� ����� �������� � ����
class TankVolumeSensorUsingUltrasonicDistanceSensor : public ITankVolumeSensor, public Component
{
public:
	// ITankVolumeSensor
	virtual float GetValue() { return currentTankVolume; };
	
	// IComponent
	virtual void OnFrame() override
	{
		short sensorValue = ultrasonicDistanceSensor->GetValue();
		
		// ���������, ��� �������� ������� �� ������� �� �������
		if (tableSensorValueCurrentCapacity.CheckXLimits(sensorValue))
		{
			// ������������ �������� ������� ��� �������
			return;
		}
		
		// ��������� ������� �������� �� �������
		currentTankVolume = tableSensorValueCurrentCapacity.GetValue(sensorValue);
	}
	
private:
	float currentTankVolume;
	UltrasonicDistanceSensor * ultrasonicDistanceSensor;
	
	// ������� ��������������� ������������ ����� ������� �������� � ����
	// (�� �������� �������) � ������� ��������
	LinearSpline* tableSensorValueCurrentCapacity = nullptr;
}

// TODO �������� ��������
class TankVolumeSensorUsingFillingConnectedTank : public ITankVolumeSensor
{
public:
	// ITankVolumeSensor
	virtual float GetValue()
	{
		return currentVolumeInSystemConnectedTanks - connectedTank->GetCurrentCapacity();
	};
	
	virtual void OnFrame override
	{
		// ��������� ������� ����� �������� � ������� ������������ �������
		// ����������� ��� ������������ �������� �������� � ������������ ����
		// �� ����������� ��������
		
		// TODO
		float currentVolumeInConnectedTank = connectedTank->GetCurrentCapacity();
	}
	
private:
	// ���������� ��� �� �������� �������� ���������� � ����
	ITank * connectedTank;	
	
	// ������� ����� �������� � ������� ������������ �������
	// ����������� ��� ������������ �������� �������� � ������������ ����
	// �� ����������� ��������
	float currentVolumeInSystemConnectedTanks = 0;
}