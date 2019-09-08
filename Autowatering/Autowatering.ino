#include "E:\Programming\Arduino\HappyArduinoLib\HappyArduinoLib\ESP8266WebServerComponent.h"
#include "E:\Programming\Arduino\HappyArduinoLib\HappyArduinoLib\RTCComponent.h"
#include "E:\Programming\Arduino\HappyArduinoLib\HappyArduinoLib\RelayComponent.h"
#include "E:\Programming\Arduino\HappyArduinoLib\HappyArduinoLib\List.h"

ESP8266WebServerComponent WebServer("ESP8266WebServer","MGTS_GPON_8044","NHBK4MKH",80);
RTCComponent rtcComponent("RTC_DS3231");
RelayComponent relay("Relay_On_Pump", 2);

class ScheduledEventManagerComponent : Component
{
public:
  struct TimerEvent
  {    
    // Время наступления события
    DateTime dateTime;

    // Описание события
    String description;

    // Конструктор
    TimerEvent(DateTime _dateTime, const char* _description) : dateTime(_dateTime), description(_description) {}
  
    // Функция которое вызывается при наступлении события
    virtual void OnEvent() {};
  };  

private:  
  RTCComponent* rtcComponent;
  List<TimerEvent*> futureEvents;
  List<TimerEvent*> pastEvents;

public:
  ScheduledEventManagerComponent(const char* _name, RTCComponent * _rtcComponent)
    : Component(_name), rtcComponent(_rtcComponent) {};  
  
  virtual void OnFrame()
  {
    DateTime now = rtcComponent->rtc.now();
    List<TimerEvent*>::ListNode* firstFutureEvent = futureEvents.First();
    while (firstFutureEvent != NULL && (*firstFutureEvent)->dateTime < now)
    {      
      (*firstFutureEvent)->OnEvent();
      futureEvents.erase(firstFutureEvent);
      pastEvents.push_back(firstFutureEvent);
      firstFutureEvent = futureEvents.First();
    }
  }
  
  virtual void GetKeyValues(KeyValue *keyValues, short &size)
  {    
    List<TimerEvent*>::ListNode* eventNode = pastEvents.First();
    while (eventNode != NULL)
    {      
      keyValues[size] = KeyValue((*eventNode)->description, "Наступило"); size++;      
      eventNode = eventNode->Next();
    }

    eventNode = futureEvents.First();
    while (eventNode != NULL)
    {      
      keyValues[size] = KeyValue((*eventNode)->description, "Ожидается"); size++;      
      eventNode = eventNode->Next();
    }
  }

  void AddEvent(TimerEvent * newEvent)
  {
    DateTime now = rtcComponent->rtc.now();
    if (now < newEvent->dateTime)    
    {
      List<TimerEvent*>::ListNode* eventNode = futureEvents.First();
      if (eventNode == NULL)
        futureEvents.push_front(newEvent);
      else
      {
        while (eventNode != NULL && (*eventNode)->dateTime < newEvent->dateTime )           
          eventNode = eventNode->Next();
          
        if (eventNode == NULL)
          futureEvents.push_back(newEvent);
        else
          futureEvents.insert(newEvent, eventNode);
      }
    }
    else
    {
      pastEvents.push_back(newEvent);
    }     
  }
};

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
/*
  {
    // Test
    DateTime now = rtcComponent.rtc.now();    
    char date[11], time[8];
    for (unsigned short i = 2; i < 3; ++i)
    {
      if (now.minute() + i >= 60)
        continue;

      DateTime dateTime = now + TimeSpan(i * 60);      
      sprintf(date, "Sep %02d %04d", dateTime.day(), dateTime.year());
      sprintf(time, "%02d:%02d:%02d", dateTime.hour(), dateTime.minute(), dateTime.second());
      CreateAutoWateringEvent(date, time, 90); // Вс
    }
  }*/

  // TEST
  CreateAutoWateringEvent("Sep 08 2019", "00:13:00", 10); // Вс
  
  CreateAutoWateringEvent("Sep 08 2019", "09:00:00", 90); // Вс
  CreateAutoWateringEvent("Sep 12 2019", "13:00:00", 90); // Чт
  CreateAutoWateringEvent("Sep 16 2019", "13:00:00", 90); // Пн
  CreateAutoWateringEvent("Sep 19 2019", "13:00:00", 90); // Чт
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
