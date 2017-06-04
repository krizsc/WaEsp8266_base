#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <FS.h>

const char* ssid = "T-Home_4FE92A";
const char* password = "33fvcuja";

ESP8266WebServer server(80);

const int led = 13;

void handleRoot() {
 	digitalWrite(led, 1);
 	server.send(200, "text/plain", "hello from esp8266!");
	digitalWrite(led, 0);
}

void handleNotFound(){
	digitalWrite(led, 1);
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
	digitalWrite(led, 0);
}

void setup(void){
	pinMode(led, OUTPUT);
	digitalWrite(led, 0);
	Serial.begin(115200);
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

	Serial.println("Entry points");
	/*server.on("/", handleRoot);

	server.on("/inline", [](){
	//	server.send(200, "text/plain", "this works as well");
		server.send(200, "html", "<html><head><title>Esp8266 test</title></head><body><h1>This is a title</h1><p>This is a paragraph</p><ul><li>option 1</li><li>option 2</li><li>option 3</li></ul></body></html>");
	})*/;

	server.onNotFound(handleNotFound);

	Serial.println("Starting server on " + WiFi.localIP());
	server.begin();
	Serial.println("HTTP server started");
}

unsigned int cnt = 0;

void loop(void){
	server.handleClient();

}
