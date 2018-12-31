/*
 * main.cpp
 *
 *  Created on: 2018/12/31
 *      Author: Shuji
 */
#include <Arduino.h>
#include <WiFi.h>

bool status = true;
void setup()
{

	Serial.begin(115200);
	Serial.println("Program Start");
	Serial.println("Scan Wifi access points");

	Serial.print("Setting Wifi to station mode...");
	status = WiFi.mode(WIFI_MODE_STA);

	if(status){
		Serial.println("done");
	}
	else{
		Serial.println("failed");
	}

	if(status){
		Serial.print("Disconnect...");
		status = WiFi.disconnect();
	}

	if(status){
		Serial.println("done");
	}
	else{
		Serial.println("failed");
	}
}
void loop()
{
	if(status){
		Serial.println("Program Running");

		int16_t numOfFoundAP = WiFi.scanNetworks();

		if(numOfFoundAP > 0){
			Serial.printf("%d access points found.\r\n", numOfFoundAP);

			for(int i = 0; i < numOfFoundAP; i++){
				Serial.print(((WiFiScanClass)WiFi).SSID(i));
				Serial.print(",");
				Serial.println(((WiFiScanClass)WiFi).RSSI(i));
			}

			Serial.println();
			delay(1000);
		}
		else{
			Serial.println("No access points found.");
		}

	}

}



