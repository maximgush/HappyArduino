#include <Servo.h>

#define echoPin 4 // Echo Pin
#define trigPin 0 // Trigger Pin

/*define a header file. Special attention here, you can call the servo function directly from Arduino's software menu bar Sketch>Importlibrary>Servo, or input  #include <Servo.h>. Make sure there is a space between #include and  <Servo.h>. Otherwise, it will cause compile error. */
Servo myservo;// define servo variable name
void setup()
{
    Serial.begin(115200);
    myservo.attach(2, 45, 135);// select servo pin(9 or 10)
    myservo.write(90);// set rotate angle of the motor

    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

void loop()
{
/*    short visionAngles[] = { 45, 135 };
    short visionAnglesSize = 2;
    myservo.attach(2);

    for (int j = 0; j < visionAnglesSize; ++j)
    {
      myservo.write(visionAngles[j]);     
      for (int i = 0; i < 10; ++i)
      {     
        digitalWrite(trigPin, LOW); 
        delayMicroseconds(2);       
  
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10); 
        digitalWrite(trigPin, LOW);
        long duration = pulseIn(echoPin, HIGH);
   
        //Calculate the distance (in cm) based on the speed of sound.
        long distance = duration/58.2;
  
        Serial.println(String("Angle = " ) + visionAngles[i] + "     Distance = " + distance);
  
        delay(100); 
      }
    }
*/
        digitalWrite(trigPin, LOW); 
        delayMicroseconds(2);       
  
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10); 
        digitalWrite(trigPin, LOW);
        long duration = pulseIn(echoPin, HIGH);
   
        //Calculate the distance (in cm) based on the speed of sound.
        long distance = duration/58.2;
  
        Serial.println(distance);
  
        delay(100);
} 
