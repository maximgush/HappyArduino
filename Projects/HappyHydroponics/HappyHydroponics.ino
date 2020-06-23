#include "G:\Repos\HappyArduino2\HappyArduinoLib\ESP8266WebServerComponent.h"
#include "G:\Repos\HappyArduino2\HappyArduinoLib\RTCComponent.h"
#include "G:\Repos\HappyArduino2\HappyArduinoLib\RelayComponent.h"
#include "G:\Repos\HappyArduino2\HappyArduinoLib\UltrasonicDistanceSensorComponent.h"
#include "G:\Repos\HappyArduino2\HappyArduinoLib\ScheduledEventManager.h"

ESP8266WebServerComponent WebServer("ESP8266WebServer","MGTS_GPON_8044","NHBK4MKH",80);
RTCComponent rtcComponent("RTC_DS3231");
RelayComponent relay("Relay_On_Pump", 0);
UltrasonicDistanceSensorComponent ultrasonicDistanceSensor("Ultrasonic distance sensor for measuring the volume of water in the lower tank", 14, 12);

ScheduledEventManagerComponent eventManager("EventManager", &rtcComponent);

struct RelayOnTimerEvent : public ScheduledEventManagerComponent::TimerEvent
{
  RelayOnTimerEvent(DateTime _dateTime, const char* _description)
     : TimerEvent(_dateTime,_description) {}
  
  virtual void OnEvent()
  {
    relay.On();
    Serial.println("-------> Relay On");
  };
};

struct RelayOffTimerEvent : public ScheduledEventManagerComponent::TimerEvent
{
  RelayOffTimerEvent(DateTime _dateTime, const char* _description)
     : TimerEvent(_dateTime,_description) {}
     
  virtual void OnEvent()
  {
    relay.Off();
    Serial.println("-------> Relay Off");
  };
};

void CreateAutoWateringEvent(const char* _date, const char* _time, unsigned short _durationSec)
{ 
  DateTime dateTimeOn(_date,_time);  
  char descr[100];
  sprintf(descr, "Автоматический полив %02u.%02u.%04u %02u:%02u:%02u. Начало", dateTimeOn.day(), dateTimeOn.month(), dateTimeOn.year(), dateTimeOn.hour(), dateTimeOn.minute(), dateTimeOn.second());
  eventManager.AddEvent(new RelayOnTimerEvent(dateTimeOn,  descr));

  DateTime dateTimeOff = dateTimeOn + TimeSpan(_durationSec);
  sprintf(descr, "Автоматический полив %02u.%02u.%04u %02u:%02u:%02u. Конец", dateTimeOff.day(), dateTimeOff.month(), dateTimeOff.year(), dateTimeOff.hour(), dateTimeOff.minute(), dateTimeOff.second());
  eventManager.AddEvent(new RelayOffTimerEvent(dateTimeOff, descr));
}

void setup(){ 
  Serial.begin(115200);     // Communication started with 9600 baud
  
  ComponentsContainer::Instance().Init(); 
  
  // TEST
  CreateAutoWateringEvent("Sep 28 2019", "14:34:00", 10); // Вс  
}

void loop(){
  ComponentsContainer::Instance().OnFrame();

  if (ultrasonicDistanceSensor.GetDistance() > 10)
    relay.On();
  else
    relay.Off();
  
  Serial.print(relay.IsOn());
  Serial.print(" ---- ");
  Serial.println(ultrasonicDistanceSensor.GetDistance());

  delay(1000);
}
