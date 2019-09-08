#include "E:\Programming\Arduino\HappyArduinoLib\HappyArduinoLib\WaterLevelSensorComponent.h"
#include "E:\Programming\Arduino\HappyArduinoLib\HappyArduinoLib\RTCComponent.h"
#include "E:\Programming\Arduino\HappyArduinoLib\HappyArduinoLib\RelayComponent.h"
#include "E:\Programming\Arduino\HappyArduinoLib\HappyArduinoLib\ESP8266WebServerComponent.h"
#include "E:\Programming\Arduino\HappyArduinoLib\HappyArduinoLib\LM35TempSensorComponent.h"

ESP8266WebServerComponent WebServer("ESP8266WebServer","MGTS_GPON_8044","NHBK4MKH",80);
WaterLevelSensorComponent waterLevelSensor("WaterLevelSensor1", A0);
RTCComponent rtcComponent("RTC_DS3231");
RelayComponent relay("Relay_On_Pump", 2);
LM35TempSensorComponent LM35TempSensor("LM 35 Temp Sensor", A0);

void setup(){
  delay(3000); // wait for console opening
  Serial.begin(115200);     // Communication started with 9600 baud
  ComponentsContainer::Instance().Init();
}

void loop(){
  ComponentsContainer::Instance().OnFrame();

  DateTime now = rtcComponent.rtc.now();  
  if ( now.minute() % 20 < 8 )
    relay.On();
  else
    relay.Off(); 
  
  Serial.println(relay.IsOn());
  Serial.println(waterLevelSensor.GetValue());

  int value = waterLevelSensor.GetValue(); //Read data from analog pin and store it to value variable

  delay(1000);
}
