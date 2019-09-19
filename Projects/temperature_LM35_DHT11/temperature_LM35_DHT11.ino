// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

#include "DHT.h"

#define DHTPIN 8     // what pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11 
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

DHT dht(DHTPIN, DHTTYPE);
int potPin = 0; // initialize analog pin 0 for LM35 temperature sensor

void setup()
{

  Serial.begin(9600);
  Serial.println("DHTxx test!");

  /*if using WIO link,must pull up the power pin.*/
  // pinMode(PIN_GROVE_POWER, OUTPUT);
  // digitalWrite(PIN_GROVE_POWER, 1);

  dht.begin();
}

void loop()
{
  int val;// define variable
  int dat;// define variable
  val = analogRead(0); // read the analog value of the sensor and assign it to val
  dat = (125 * val) >> 8; // temperature calculation formula
  Serial.print("Tep:");// output and display characters beginning with Tep
  Serial.print(dat);// output and display value of dat
  Serial.println("C");// display “C” characters
  delay(500);// wait for 0.5 second
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // check if returns are valid, if they are NaN (not a number) then something went wrong!
  if (isnan(t) || isnan(h))
  {
    Serial.println("Failed to read from DHT");
  }
  else
  {
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.println(" *C");
  }
}
