/*
    HTTP over TLS (HTTPS) example sketch

    This example demonstrates how to use
    WiFiClientSecure class to access HTTPS API.
    We fetch and display the status of
    esp8266/Arduino project continuous integration
    build.

    Limitations:
      only RSA certificates
      no support of Perfect Forward Secrecy (PFS)
      TLSv1.2 is supported since version 2.4.0-rc1

    Created by Ivan Grokhotkov, 2015.
    This example is in public domain.
*/

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

#ifndef STASSID
const char* STASSID     = "MGTS_GPON_8044";
const char* STAPSK = "NHBK4MKH";
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

const char* host = "144.217.74.219";
const int httpsPort = 3128;

// Use web browser to view and copy
// SHA1 fingerprint of the certificate
const char fingerprint[] PROGMEM = "‎16 27 ac a5 76 28 2d 36 63 1b 56 4d eb df a6 48";

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Use WiFiClientSecure class to create TLS connection
  WiFiClient client;
  Serial.print("connecting to ");
  Serial.println(host);

  //Serial.printf("Using fingerprint '%s'\n", fingerprint);
  //client.setFingerprint(fingerprint);
  //client.setInsecure();

  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }

  //String url = "https://api.telegram.org/bot888279741:AAFNvWADtq0HmGfZvR8M8ZMQZYtf4xh6_Pk/sendMessage?chat_id=405389021&text=HelloFromArduino";
  //String url = "https://example.com";
 // Serial.print("requesting URL: ");
 // Serial.println(url);

    String token = "888279741:AAFNvWADtq0HmGfZvR8M8ZMQZYtf4xh6_Pk";
    String chat_id = "405389021";
    String msg = "HelloFromArduino";
    String url = "https://api.telegram.org";
    client.println("GET " + url + "/bot"+token+"/sendMessage?chat_id=" + chat_id + "&text=" + msg + " HTTP/1.1");
    client.println("Host: ") + host;
    client.println("Accept: */*");
    //client.println("Content-Type: application/json");
    //client.println("Connection: close");
    //client.print("Content-Length: ");
    /*client.println(msg.length());
    client.println();
    client.println(msg);*/
/*      // Make a HTTP request through proxy:
    client.print(String("POST ") + url + " HTTP/1.2\r\n" + String("Host: ") + host + "\r\n");
    client.println("User-Agent: curl/7.37.1");
    client.println();*/
  //client.println(String("GET ") + url);  
                //+ " HTTP/1.2\r\n"
               //+ String("Host: ") + host + "\r\n";
               //"User-Agent: BuildFailureDetectorESP8266\r\n" +
               //"Connection: close\r\n\r\n");*/
  //client.println();  

  Serial.println("request sent");
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }
  for (int i = 0; i < 50; ++i)
  {
    String line = client.readStringUntil('\n');
    Serial.println(line);
  }
 /* 
  if (line.startsWith("{\"state\":\"success\"")) {
    Serial.println("esp8266/Arduino CI successfull!");
  } else {
    Serial.println("esp8266/Arduino CI has failed");
  }
  Serial.println("reply was:");
  Serial.println("==========");
  //Serial.println(line);
  Serial.println("==========");
  Serial.println("closing connection");*/
}

void loop() {
}
