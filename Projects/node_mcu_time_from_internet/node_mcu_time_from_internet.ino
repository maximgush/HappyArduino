#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>



const char *ssid     = "MGTS_GPON_8044";
const char *password = "NHBK4MKH";
//const char *ssid     = "Happy Redmi 4X";
//const char *password = "wbvxeuqm";


const long utcOffsetInSeconds = 7200;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

void setup(){
  Serial.begin(115200);
    pinMode(D0, OUTPUT);     // Initialize the LED_BUILTIN pin as an output

  WiFi.begin(ssid, password);

  while( WiFi.status() != WL_CONNECTED )
  {
    digitalWrite(D0, HIGH);
    delay( 500 );
    Serial.print( "!" );
    digitalWrite(D0, LOW);
  }

  timeClient.begin();
}

void loop() {
  timeClient.update();

  Serial.print(daysOfTheWeek[timeClient.getDay()]);
  Serial.print(", ");
  Serial.print(timeClient.getHours());
  Serial.print(":");
  Serial.print(timeClient.getMinutes());
  Serial.print(":");
  Serial.println(timeClient.getSeconds());
  //Serial.println(timeClient.getFormattedTime());

  delay(1000);
}
