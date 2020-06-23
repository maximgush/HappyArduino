#include <ESP8266WebServerComponent.h>
//#include <RTCComponent.h>
#include <RelayComponent.h>
//#include <ScheduledEventManager.h>
#include <Component.h>

#include <interfaces/IRTC.h>
#include <NTPClient.h>

class RTCNetworkTimeComponent : public IRTC, public Component
{
public:
  RTCNetworkTimeComponent( const char* _name, const long _utcOffsetInSeconds );

  // Component
  virtual void Init() override;
  virtual void OnFrame() override;
  virtual void GetKeyValues( KeyValue *keyValues, short &size ) const override;
  
  // IRTC
  virtual CDateTime GetCurrentTime() const override;

  // Обновить время из интернета  
  void UpdateTime();
  
private:
  WiFiUDP ntpUDP;
  NTPClient timeClient;
  mutable CDateTime dateTimeOnLastSyncro; // Время полученное пз интернета во время последней синхронизации
  mutable unsigned long millisFromStartProgramOnSyncro = 0; // количество мс от старта программы когда произошла последняя синхронизация время с интернетом
};

RTCNetworkTimeComponent::RTCNetworkTimeComponent( const char* _name, const long _utcOffsetInSeconds )
  : Component( _name )
  , timeClient(ntpUDP, "pool.ntp.org", _utcOffsetInSeconds)
{
}

void RTCNetworkTimeComponent::Init()
{
  timeClient.begin();
}

void RTCNetworkTimeComponent::OnFrame()
{  
  UpdateTime();
};

void RTCNetworkTimeComponent::UpdateTime()
{
  timeClient.update();
  millisFromStartProgramOnSyncro = millis();
  dateTimeOnLastSyncro = CDateTime (timeClient.getYear(), timeClient.getMonth(), timeClient.getDay(), timeClient.getHours(), timeClient.getMinutes(), timeClient.getSeconds() );    
}

void RTCNetworkTimeComponent::GetKeyValues( KeyValue *keyValues, short &size ) const
{
  CDateTime currentTime = GetCurrentTime();
  char timeStr[10];
  sprintf( timeStr, "%02d:%02d:%02d", currentTime.hour(), currentTime.minute(), currentTime.second() );
  keyValues[size] = KeyValue( "Текущее время", timeStr ); size++;
  sprintf( timeStr, "%02d:%02d:%4d", currentTime.day(), currentTime.month(), currentTime.year() );
  keyValues[size] = KeyValue( "Текущее дата", timeStr ); size++;
}

CDateTime RTCNetworkTimeComponent::GetCurrentTime() const
{
  unsigned long timeFromStartProgram = millis();
  CDateTime currentTime = dateTimeOnLastSyncro;
  currentTime = currentTime + CTimeSpan(( timeFromStartProgram - millisFromStartProgramOnSyncro ) / 1000);

  // Обработам возможное переполнение millis()
  if ( timeFromStartProgram < millisFromStartProgramOnSyncro) {
    dateTimeOnLastSyncro = currentTime;
    millisFromStartProgramOnSyncro = timeFromStartProgram;
  }

  return currentTime;
}

ESP8266WebServerComponent WebServer("ESP8266WebServer","MGTS_GPON_8044","NHBK4MKH",80);
//RTCComponent rtcComponent("RTC_DS3231");
RelayComponent relay("Relay_On_Pump", D0);
RTCNetworkTimeComponent rtcComponent("RTCNetworkTimeComponent", 10800);

/*
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
*/
void setup(){ 
  Serial.begin(115200);     // Communication started with 9600 baud
  
  ComponentsContainer::Instance().Init(); 

  // TEST
  //CreateAutoWateringEvent("Dec 24 2019", "15:00:00", 35); // Вс  
  //CreateAutoWateringEvent("Dec 27 2019", "15:00:00", 35); // Вс  
}

void loop(){
  ComponentsContainer::Instance().OnFrame();
  
  CDateTime currentTime = rtcComponent.GetCurrentTime();
  char timeStr[20];
  sprintf( timeStr, "%02d:%02d:%4d  %02d:%02d:%02d", currentTime.day(), currentTime.month(), currentTime.year(), currentTime.hour(), currentTime.minute(), currentTime.second() );
  Serial.println(timeStr);

  delay(1000);
}
