/*
 Name:		HappyHidroponics.ino
 Created:	11.08.2019 2:36:34
 Author:	Максим
*/

#include "common.h"

#include "Component.h"
//#include "RTCComponent.h"

//RTCComponent rtc("RTC DS3231");

// the setup function runs once when you press reset or power the board
void setup() {
	ComponentsContainer::Instance().Init();
}

// the loop function runs over and over again until power down or reset
void loop() {
	ComponentsContainer::Instance().OnFrame();
}

#include <HappyArduinoLib/Utils/Array.h>

int main()
{
	setup();

	for (;;)
		loop();

	return 0;
}
