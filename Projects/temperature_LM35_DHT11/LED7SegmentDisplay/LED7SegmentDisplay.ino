#include "LED7SegmentDisplay.h"

unsigned int displayCathodePins[8] = {1,2,3,4,5,6,7,8};
unsigned int displayAnodePins[4] = {9,10,11,12};
LED7SegmentDisplay display(4, displayCathodePins, displayAnodePins );

#include "RTClib.h"
RTC_DS3231 rtc;

void setup()
{
  Serial.begin(9600);
  display.Init();   
/*
#ifndef ESP8266
  while (!Serial); // for Leonardo/Micro/Zero
#endif

  Serial.begin(9600);

  delay(3000); // wait for console opening

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }*/
}
/////////////////////////////////////////////////////////////
void loop()
{
 // DateTime now = rtc.now();
 // int time = now.hour() * 100 + now.minute();

  delay(1000/100);
  //int time = millis() / 1000;
  //display.DisplayTime(now.hour(), now.minute()); 
  display.DisplayInt("1"); 
}
///////////////////////////////////////////////////////////////
