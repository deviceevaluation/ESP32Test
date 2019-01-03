/*
 * main.cpp
 *
 *  Created on: 2019/01/03
 *      Author: Shuji
 */
#include <Arduino.h>
#include "WiFi.h"
bool status = true;

const int SERVER_PORT = 80;
const char SSID[] = "IODATA-6da6a4-2G";
const char PASSWD[] = "2426469930683";
const int CONNECTION_TIMEOUT = 20;

const char NTP[] = "ntp-b1.nict.go.jp";
const char URL[] = "/cgi-bin/time";

String createGETMeathod(const char* host, const char* url);

void setup()
{
	Serial.begin(115200);

	Serial.println("WiFi Client Test");

	status = WiFi.begin(SSID,PASSWD);

	if(status){
		Serial.print("Connecting to ");
		Serial.println(SSID);

		int cntLim = 0;
		while(WiFi.status() != WL_CONNECTED){
			delay(1000);
			cntLim++;

			if(cntLim >= CONNECTION_TIMEOUT){
				Serial.println("Failed to connect.");
				status = false;
				break;
			}
		}
	}

	if(status){
		IPAddress localAddress = WiFi.localIP();
		Serial.println(localAddress.toString());
	}

}
void loop()
{
	delay(5000);

	WiFiClient client;

	if(status){
		Serial.print("connecting to ");
		Serial.println(NTP);

		if(!client.connect(NTP, 80)){
			status = false;
			Serial.println("failed to connect.");
		}
	}


	if(status){
		Serial.print("Request to ");
		Serial.println(NTP);

		client.print(createGETMeathod(NTP, URL));

		int cntLim = 0;
		while(client.available() == 0){
			delay(1000);
			cntLim++;

			if(cntLim >= CONNECTION_TIMEOUT){
				Serial.println("No reply.");
				break;
			}
		}

		while(client.available()){
			String readLine = client.readStringUntil('\r');
			Serial.println(readLine);
		}

		Serial.println();
		Serial.println("connection close.");
	}
}

String createGETMeathod(const char* host, const char* url)
{
	String result = "GET ";

	if(url != NULL){
		result += String(url);
		result += " ";
	}

	result += "HTTP/1.1\r\n";

	result += "Host: ";

	result += String(host);

	result += "\r\n";

	result += "Connection: close\r\n\r\n";

	return result;
}
