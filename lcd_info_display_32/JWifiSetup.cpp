/*
 Name:		JWifiSetup.cpp
 Created:	10/6/2019 12:16:27 PM
 Author:	Jens Marchewka
*/

#include <WebServer.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <ESPmDNS.h>
#include <FS.h>
#include <SPIFFS.h>
#include <SPI.h>
#include <WiFiAP.h>

#include "JWifiSetup.h"
#include "JwifiSetupHtml.h"

JWifiSetup::JWifiSetup(String configFileName, String wifiName, String wifiPassword) {
	this->_configFileName = configFileName;
	this->_wifiName = wifiName;
	this->_wifiPassword = wifiPassword;
}

JWifiSetup::~JWifiSetup() {
	this->_webServer.close();
}

JWifiData* JWifiSetup::GetWifi(bool forceReset = false) {
	if (!forceReset) {
		this->_wifiData = this->tryReadWifiData();
		if (this->_wifiData != NULL) {
			Serial.print("CONFIG SSID:"); Serial.println(this->_wifiData->ssid);
			Serial.print("CONFIG PWD:"); Serial.println(this->_wifiData->passwd);
			return this->_wifiData;
		}
	}

	// Start Access Point
	WiFi.softAP(this->_wifiName.c_str(), this->_wifiPassword.c_str());
	IPAddress myIP = WiFi.softAPIP();
	Serial.print("AP IP address: ");
	Serial.println(myIP);


	this->_webServer.on("/", [this]() {
		this->_webServer.send(200, "text/html", JWifiSetup_HTML_FORM);
	});
	this->_webServer.on("/submit_wifi_data", [this]() {
		String ssid = this->_webServer.arg("ssid");
		String passwd = this->_webServer.arg("password");
		
		Serial.print("USER INPUT SSID:"); Serial.println(ssid);
		Serial.print("USER INPUT PWD:"); Serial.println(passwd);

		if (ssid.length() > 0) {
			this->_webServer.send(200, "text/html", JWifiSetup_HTML_SUCCESS);
			JWifiData *	d = new JWifiData();
			memset(d->ssid, 0, 128);
			memset(d->passwd, 0, 128);
			memcpy(d->ssid, ssid.c_str(), max(127U, ssid.length()));
			memcpy(d->passwd, passwd.c_str(), max(127U, passwd.length()));
			this->_wifiData = d;
			return;
		}
		this->_webServer.send(200, "text/html", JWifiSetup_HTML_FORM);
	});

	Serial.println("Opening WebServer...");
	this->_webServer.begin();
	Serial.println("Opened.");

	while (!this->_wifiData) {
		this->_webServer.handleClient();
	}
	this->tryWriteWifiData();
	Serial.println("Closing WebServer...");
	this->_webServer.close();
	Serial.println("Closed.");

	return this->_wifiData;
}

void JWifiSetup::RemoveWifiConfig() {
	if (!SPIFFS.begin()) {
		Serial.println("Formating file system");
		SPIFFS.format();
		SPIFFS.begin();
	}
	
	if (SPIFFS.exists(this->_configFileName)) {
		SPIFFS.remove(this->_configFileName);
	}
}

void JWifiSetup::tryWriteWifiData() {
	// check file system exists
	if (!SPIFFS.begin()) {
		Serial.println("Formating file system");
		SPIFFS.format();
		SPIFFS.begin();
	}

    File fConfigFile = SPIFFS.open(this->_configFileName, "w");
    if (fConfigFile) {
		fConfigFile.write((uint8_t*)this->_wifiData, sizeof(JWifiData));
		fConfigFile.close();
    }
}

JWifiData* JWifiSetup::tryReadWifiData() {
	// check file system exists
	if (!SPIFFS.begin()) {
		Serial.println("Formating file system");
		SPIFFS.format();
		SPIFFS.begin();
	}

	// check if setupfile file exists and size is correct
	if (SPIFFS.exists(this->_configFileName)) {
		File fConfigFile = SPIFFS.open(this->_configFileName, "r");
		if (fConfigFile) {
			uint8_t bufferRead[sizeof(JWifiData)];
			if (fConfigFile.read(bufferRead, sizeof(JWifiData)) == sizeof(JWifiData)) {
				return reinterpret_cast<JWifiData*>(bufferRead);
			}
			fConfigFile.close();
		}
	}

	return NULL;
}