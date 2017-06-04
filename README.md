# WaEsp8266_base
First version of a small SPIFFS based webserver on the Esp8266 controller.

Put all HTML/CSS/JS/Data files into their respectible folders in the data/ directory.
If you want to create a new folder, you will have to add using the server.serveStatic() method in the setup() function.
For example: server.serveStatic("/example/", SPIFFS, "/example/");
A local WiFi SSID and password also have to be provided in the beginning of the program
