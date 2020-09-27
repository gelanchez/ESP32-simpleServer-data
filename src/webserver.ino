/**
 * @file webserver.ino
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Main implementation of the webserver to control a LED and present.
 * data from the sensors to the clients.
 * Two webservers and technologies can be used:
 * a) Simple webserver + jQuery AJAX.
 * b) Async webserver + websockets.
 * @version 0.0.1
 * @date 2020-09-20
 * @copyright GPL-3.0
 */

#define ESP32

#include <Arduino.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "constants.h"
#include <WiFi.h>

AsyncWebServer g_asyncServer(80);

void setup()
{
    Serial.begin(115200);
    delay(1000);

    pinMode(Constants::ledPin, OUTPUT);

    /**
     * @brief Connect to WiFi
     */
    WiFi.config(Constants::ip, Constants::gateway, Constants::subnet);
    WiFi.begin(Constants::ssid, Constants::password);
    while (WiFi.status() != WL_CONNECTED)
        delay(1000);
    Serial.print("Connected to WiFi ");
    Serial.print(Constants::ssid);
    Serial.print(" as ");
    Serial.println(WiFi.localIP());

    g_asyncServer.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/plain", "Hello World");
        });
    g_asyncServer.onNotFound([](AsyncWebServerRequest *request){
        request->send(404, "text/plain", "Not found");
    });
    g_asyncServer.begin();
}

void loop()
{
}