#ifndef NETWORK_H
#define NETWORK_H

#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include "utils.h"

#define NETWORK_MAX_ENDPOINTS 5

namespace network
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////  Interface  //////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void connect();
	bool isWifiSaved();
	bool checkConnection();
	void resetWifi();
	void registerEndPoint(char* endPoint, void (*handler)());
	ESP8266WebServer* getWebServer();

	/* Helper Functions */
	void networkConfigModeSet(WiFiManager* myWiFiManager);
	void startServer();

	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////  Data  //////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	ESP8266WebServer server(80);
	const char* serverEndpoints[NETWORK_MAX_ENDPOINTS];
	void (*serverHandlers[NETWORK_MAX_ENDPOINTS])();
	char numEndpoints = 0;
	WiFiManager wifiManager;
	bool enteredAPMode = false;
	bool isWifiConnected = false;

	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////  Impl  //////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void connect() {
	  isWifiConnected = false;
	  enteredAPMode = false;
	  bool tryingToConnect = wifiManager.getWiFiIsSaved();

	  wifiManager.setDebugOutput(false);
	  wifiManager.setMinimumSignalQuality(25);
	  wifiManager.setAPCallback(networkConfigModeSet);
	  wifiManager.setConfigPortalBlocking(false);
	  
	  if(tryingToConnect) Serial.println(FS("Connecting to Wifi..."));
	  char idHexBuffer[4];
	  String apName = FS("PixelCon Frame (") + String(convertToHex(ESP.getChipId(), idHexBuffer, 4)) + FS(")");
	  wifiManager.autoConnect(apName.c_str());

	  // wait until connection is attempted
	  while(!(enteredAPMode || WiFi.status() == WL_CONNECTED)) {
		wifiManager.process();
	  }
	  if(tryingToConnect) {
		if(enteredAPMode) {
		  Serial.println(FS("Failed to connect to WiFi"));
		} else {
		  isWifiConnected = true;
		  startServer();
		  Serial.print(FS("Connected to WiFi! IP Address is: "));
		  Serial.println(WiFi.localIP());
		}
	  }
	}

	void networkConfigModeSet(WiFiManager* myWiFiManager) {
	  enteredAPMode = true;
	  Serial.println(FS("Starting Wifi configuration mode"));
	}

	bool isWifiSaved() {
	  return wifiManager.getWiFiIsSaved();
	}

	bool checkConnection() {
	  wifiManager.process();
	  server.handleClient();

	  if(isWifiConnected && WiFi.status() != WL_CONNECTED) {
		Serial.println(FS("Lost WiFi connection"));
		isWifiConnected = false;
	  }

	  if(!isWifiConnected && WiFi.status() == WL_CONNECTED) {
		Serial.print(FS("Connected to WiFi! IP Address is: "));
		isWifiConnected = true;
		startServer();
		Serial.println(WiFi.localIP());
	  }

	  return (WiFi.status() == WL_CONNECTED);
	}
	
	void registerEndPoint(const char* endpoint, void (*handler)()) {
		if(numEndpoints < NETWORK_MAX_ENDPOINTS) {
			serverEndpoints[numEndpoints] = endpoint;
			serverHandlers[numEndpoints] = handler;
			numEndpoints++;
		}
	}

	void resetWifi() {
	  Serial.println(FS("Clearing WiFi settings..."));
	  WiFi.disconnect();
	  wifiManager.resetSettings();
	}
	
	ESP8266WebServer* getWebServer() {
		return &server;
	}

	void startServer() {
	  delay(1000);
	  WiFi.mode(WIFI_STA);
	  for(int i=0; i<numEndpoints; i++) {
		  server.on(FPSTR(serverEndpoints[i]), serverHandlers[i]);
	  }
	  server.begin();
	}
	
	
}

#endif /* NETWORK_H */
