#include "E:\Programming\Arduino\HappyArduinoLib\HappyArduinoLib\RTCComponent.h"

RTCComponent rtcComponent("RTC_DS3231");

void setup(){
  Serial.begin(115200);     // Communication started with 9600 baud
  ComponentsContainer::Instance().Init();
  rtcComponent.SetCurrentDateAndTime();
}

void loop(){
  ComponentsContainer::Instance().OnFrame();
  {
    DateTime now = rtcComponent.rtc.now();
    char time[8];
    sprintf(time, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());
    Serial.println(time);
  }  

  delay(1000);
}
