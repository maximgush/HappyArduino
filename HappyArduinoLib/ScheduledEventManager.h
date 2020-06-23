#pragma once

#include <Component.h>
#include <Utils\\List.h>

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