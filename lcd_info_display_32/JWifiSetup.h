/*
 Name:		RelaisSwitch.h
 Created:	10/6/2019 12:16:27 PM
 Author:	imnai
 Editor:	http://www.visualmicro.com
*/

#ifndef _JWifiSetup_h
#define _JWifiSetup_h

#include <WebServer.h>
#include <arduino.h>
#include <FS.h>
#include <SPI.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <ESPmDNS.h>
#include <WiFiAP.h>

typedef struct{
	char ssid[128];
	char passwd[128];
} JWifiData;

class JWifiSetup {
public:
	JWifiSetup(
		String configFileName, 
		String wifiName, 
		String wifiPassword);
	~JWifiSetup();

	JWifiData*			GetWifi(bool forceReset);
	JWifiData*			GetWifi(){ return this->GetWifi(false);};
	void				RemoveWifiConfig();

private:
	JWifiData* 			_wifiData;
	String 				_configFileName; 
	String 				_wifiName; 
	String 			 	_wifiPassword;
	WebServer			_webServer;

	JWifiData*			tryReadWifiData();
	void 				tryWriteWifiData();
	void				handleRoot();
};

#endif

