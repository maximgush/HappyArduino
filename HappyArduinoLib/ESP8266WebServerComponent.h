#pragma once

#include "Component.h"

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>	

class ESP8266WebServerComponent : public Component
{
private:
	static ESP8266WebServer * server;
	const char* WiFiConnectionName;
	const char* password;
	int port;
	String WiFiLocalIP;
private:
	static void handleRoot()
	{			
		String htmlCode;
		htmlCode.reserve(10000);
		htmlCode =
		"<html>\
			<head>\
				<meta http-equiv='refresh' content='5' charset=\"utf-8\"/>\
				<title>ESP8266 Demo</title>\
				<style>\
					body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
				</style>\
			</head>\
			<body>\
				<h1 style=\"font-family:verdana;\">Happy Hydroponics</h1>";				
		
		Component ** components = ComponentsContainer::Instance().GetComponentsArray();
		short size = ComponentsContainer::Instance().GetComponentsArraySize();
		for (short i = 0; i < size; i++)
		{
			htmlCode += String("<h4>Компонент ") + components[i]->GetName() +  "</h4>";
			
			short sizeKeyValues = 0;
			KeyValue keyValues[10];	
			components[i]->GetKeyValues(keyValues, sizeKeyValues);
			htmlCode += "<table border=1>";
			for (short k = 0; k < sizeKeyValues; k++)
			{
				htmlCode += String("<tr><td>") + keyValues[k].Key + "</td>";
				htmlCode += String("<td>") + keyValues[k].Value + "</td></tr>";					
				//htmlCode += String("<tr><td>") + "1abc" + "</td>";
				//htmlCode += String("<td>") + "def" + "</td></tr>";									
			}
			htmlCode += "</table>";
		}
		
		htmlCode += 	"</body>\
					</html>";
		
		server->send(200, "text/html", htmlCode.c_str());
	}

	static void handleNotFound()
	{
		//digitalWrite(led, 1);
		String message = "File Not Found\n\n";
		message += "URI: ";
		message += server->uri();
		message += "\nMethod: ";
		message += (server->method() == HTTP_GET) ? "GET" : "POST";
		message += "\nArguments: ";
		message += server->args();
		message += "\n";

		for (uint8_t i = 0; i < server->args(); i++) {
		message += " " + server->argName(i) + ": " + server->arg(i) + "\n";
		}

		server->send(404, "text/plain", message);
		//digitalWrite(led, 0);
	}
public:
	ESP8266WebServerComponent(const char* _name, const char* _WiFiConnectionName, const char* _password, int _port )
		: Component(_name)
		, port(_port)
		, WiFiConnectionName(_WiFiConnectionName)
		, password(_password)
	{	
	}
	
	virtual void Init()
	{
		if (server == nullptr)
		{
			server = new ESP8266WebServer(port);
		}
	//----------------------------------------------------- 
		Serial.println("Initialize WiFi");
		// Инициализируем WiFi и Web-сервер
		WiFi.mode(WIFI_STA);
		WiFi.begin(WiFiConnectionName, password);

		// Wait for connection
		while (WiFi.status() != WL_CONNECTED)
		{
			delay(500);
			Serial.print(".");
		}
		
		WiFiLocalIP = WiFi.localIP().toString();

		Serial.println("");
		Serial.print("Connected to ");
		Serial.println(WiFiConnectionName);
		Serial.print("IP address: ");
		Serial.println(WiFiLocalIP);

		if (MDNS.begin("esp8266"))
		{
			Serial.println("MDNS responder started");
		}

		server->on("/", ESP8266WebServerComponent::handleRoot);
		server->on("/inline", []() {
									server->send(200, "text/plain", "this works as well");
								});
		server->onNotFound(ESP8266WebServerComponent::handleNotFound);
		server->begin();
		Serial.println("HTTP server started");
	//-----------------------------------------------------  
	}
	
	virtual void OnFrame()
	{
		server->handleClient();
		MDNS.update();
	};
	
	virtual void GetKeyValues(KeyValue *keyValues, short &size) override
	{
		int msFromStart = millis();
		int sec = millis() / 1000;
		int min = sec / 60;
		int hr = min / 60;
		char upTime[8];
		sprintf(upTime, "%02d:%02d:%02d", hr, min % 60, sec % 60);		
		keyValues[size] = KeyValue("Время работы Web-сервера", upTime); size++;
	};
};

ESP8266WebServer * ESP8266WebServerComponent::server = nullptr;