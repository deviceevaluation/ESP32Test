/*
 * main.cpp
 *
 *  Created on: 2018/12/31
 *      Author: Shuji
 */
#include <Arduino.h>
#include "WiFi.h"

bool status = true;

const int SERVER_PORT = 80;
const char SSID[] = "IODATA-6da6a4-2G";
const char PASSWD[] = "2426469930683";
const int CONNECTION_TIMEOUT = 20;

WiFiServer server(SERVER_PORT);

static String createHTMLMessage(String str);
static String extractHTMLMessage(String originalMessage);

void setup()
{
	Serial.begin(115200);
	Serial.println("Program Start");
	Serial.println("Run Wifi Server");

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
		server.begin();
	}
}
void loop()
{
	if(status){
		WiFiClient client = server.available();
		if(client){
			Serial.println("new client.");
			if(client.available()){
				String request = client.readStringUntil('\r');
				Serial.println(request);
				String reply = createHTMLMessage("Hello World!");
				client.print(reply);
				Serial.println("Client disonnected");
			}
		}
	}
}
String createHTMLMessage(String str)
{
	String reply = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n";

	reply += str;

	reply += "</html>\r\n";

	return reply;
}
