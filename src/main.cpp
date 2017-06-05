/* INCLUDES	 */
#include "Arduino.h"

/* Libs for webserver and file system */
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <FS.h>

/* Libs for display and connection */
#include <Wire.h>
#include "SSD1306.h"


const char* ssid = "T-Home_4FE92A";
const char* password = "33fvcuja";

ESP8266WebServer server(80);
SSD1306 display(0x3c, D1, D2);

uint8_t cnt = 0;

void handleNotFound(){
	String message = "File Not Found\n\n";
	message += "URI: ";
	message += server.uri();
	message += "\nMethod: ";
	message += (server.method() == HTTP_GET)?"GET":"POST";
	message += "\nArguments: ";
	message += server.args();
	message += "\n";
	for (uint8_t i=0; i<server.args(); i++){
	message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
	}
	server.send(404, "text/plain", message);
}

void setup(){
	Serial.begin(115200);

	display.init();
	display.clear();
	display.display();
	Serial.println("starting display");
	display.setFont(ArialMT_Plain_24);
	display.drawString(0, 26, String(cnt));
	display.display();
	Serial.println("drawing string");

	Serial.println("Test");
	WiFi.begin(ssid, password);
	Serial.println("Starting setup");

	// Wait for connection

	while (WiFi.status() != WL_CONNECTED) {
    	delay(500);
    	Serial.print(".");
	}
	Serial.println("");
	Serial.print("Connected to ");
	Serial.println(ssid);
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());

	if (MDNS.begin("esp8266")) {
		Serial.println("MDNS responder started");
	}

	Serial.println("FS Init");
	SPIFFS.begin();
	server.serveStatic("/", SPIFFS, "/index.html", "max-age=86400");
	server.serveStatic("/img/", SPIFFS, "/img/");
	server.serveStatic("/css/", SPIFFS, "/css/");
	server.serveStatic("/js/", SPIFFS, "/js/");
	server.serveStatic("/fonts/", SPIFFS, "/fonts/");

	server.on("/toggle", [](){
		display.clear();
		display.drawString(0, 26, String(++cnt));
		display.display();
		//server.send(200, "text/plain", "this works as well");
	});

	server.onNotFound(handleNotFound);

	server.begin();
	Serial.println("HTTP server started");
}

void loop(){
	server.handleClient();
}
