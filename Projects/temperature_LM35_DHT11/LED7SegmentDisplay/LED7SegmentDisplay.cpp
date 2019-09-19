#include "Arduino.h"
#include "LED7SegmentDisplay.h"


void LED7SegmentDisplay::DrawSegmentPicture(eSegmentPictures segmentPicture, bool needPickDot)
{
if (segmentPicture == stEmpty)
	return;
      
	for (int i = 0; i < 7; ++i)
		digitalWrite(cathodePins[i], SegmentPictureLEDValues[segmentPicture][i]);

	digitalWrite(cathodePins[7], needPickDot);
}
  
LED7SegmentDisplay::LED7SegmentDisplay(unsigned int _numDigits,
										unsigned int* _cathodePins, unsigned int* _anodPins)
	: numDigits(_numDigits), cathodePins(_cathodePins), anodPins(_anodPins)
{
}

void LED7SegmentDisplay::LED7SegmentDisplay::Init()
{
    for (int i = 0; i < 8; ++i)
        pinMode(cathodePins[i], OUTPUT);

	for (int i = 0; i < numDigits; ++i)
		pinMode(anodPins[i], OUTPUT);
}

void LED7SegmentDisplay::DisplayTime(unsigned int hours, unsigned int minutes)
{
	if (hours < 0 || hours > 23)
	{
		DisplayDigit(3, spMinus);
		DisplayDigit(2, spMinus);
	}
	if (minutes < 0 || minutes > 60)
	{
		DisplayDigit(1, spMinus);
		DisplayDigit(0, spMinus);
	}

	DisplayDigit(3, hours / 10);
	DisplayDigit(2, hours % 10, true);
	DisplayDigit(1, minutes / 10);
	DisplayDigit(0, minutes % 10);
}
	
  
void LED7SegmentDisplay::DisplayInt(int num)
{ 
	int minValue = -pow(10,numDigits-1) + 1;     
	int maxValue = pow(10,numDigits) - 1;
	if (num < minValue || num > maxValue)
	{
		for (int i = 0; i < numDigits; ++i)
			DisplayDigit(i, spMinus);
		return;
	}

	bool isNegative = num < 0;
	if (isNegative)
		num = -num;

	// ��������� ����� �� �����
	int i = 0;
	for (; i < numDigits; i++ )
	{
		eSegmentPictures picture = num % 10;
		num = num / 10;

		// Tckb
		if (num != 0 || picture != sp0 || i == 0)
			DisplayDigit(i, picture);               
      
		if (num == 0)
			break;
	}

    if (isNegative)
		DisplayDigit(i+1, spMinus);
}

void LED7SegmentDisplay::SetDigitNumberForChangePicture(unsigned char digitNumber)
{
	// �� ������ ������� LOW ���������� �� ���� ��������������� ����� ������
    // ������� ����� ����������
	for (int i = 0; i < numDigits; i++)
		digitalWrite(anodPins[i], digitNumber != i ? HIGH : LOW);
}
    
void LED7SegmentDisplay::Clear()  // clear the screen
{
	// TODO ������� �������
    for (int i = 0; i < 8; ++i)
		digitalWrite(cathodePins[i], LOW);
}
    
void LED7SegmentDisplay::DisplayDigit(unsigned char digitNumber, eSegmentPictures segmentPicture, bool needPickDot = false)//  take x as coordinate and display number
{
	SetDigitNumberForChangePicture(digitNumber);      
    DrawSegmentPicture(segmentPicture, needPickDot);      
    Clear();
}
