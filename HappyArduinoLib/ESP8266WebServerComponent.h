#pragma once

#include <Component.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

class ESP8266WebServerComponent : public Component
{
public:
	ESP8266WebServerComponent( const char* _name,
		const char* _WiFiConnectionName, const char* _password, int _port );

	// Component
	virtual void Init() override;	
	virtual void OnFrame() override;
	virtual void GetKeyValues( KeyValue *keyValues, short &size ) const override;

private:
	static ESP8266WebServer * server;
	const char* WiFiConnectionName;
	const char* password;
	int port;
	String WiFiLocalIP;

	void initializeWiFiConnection();
	static void handleRoot();
	static void handleNotFound();
};