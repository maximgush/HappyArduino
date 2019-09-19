#include "RTClib.h"
RTC_DS3231 rtc;

#include <Wire.h>


int Relay = 8;
void setup()
{
  pinMode(14, OUTPUT);         //Set Pin13 as output
  digitalWrite(14, HIGH);     //Set Pin13 High
 // pinMode(Relay, OUTPUT);     //Set Pin3 as output

  #ifndef ESP8266
  while (!Serial); // for Leonardo/Micro/Zero
#endif

  Serial.begin(115200);

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
  }
}


char Time[]     = "  :  :  ";
char Calendar[] = "  /  /20  ";
char temperature[] = " 00.00";
char temperature_msb;
byte i, second, minute, hour, day, date, month, year, temperature_lsb;

void loop()
{
  DateTime now = rtc.now();
  int time = now.hour() * 100 + now.minute();
  Serial.print(now.hour(),DEC);
  Serial.print(":");
  Serial.print(now.minute(),DEC);
  Serial.print(":");
  Serial.println(now.second(),DEC);

  if (now.second() % 10 < 5)
    digitalWrite(Relay, HIGH);   //Turn on relay
  else
    digitalWrite(Relay, LOW);   //Turn off relay

 Serial.print(":");
  digitalWrite(14, HIGH);
  digitalWrite(Relay, HIGH);   //Turn on relay
  delay(1000);
  digitalWrite(14, LOW);
  digitalWrite(Relay, LOW);   //Turn off relay
  delay(1000);
}
