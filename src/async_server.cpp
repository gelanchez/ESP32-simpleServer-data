/**
 * @file async_server.cpp
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Async webserver + websockets.
 * @version 0.0.1
 * @date 2020-09-26
 * @copyright GPL-3.0
 */

#ifndef ESP32
#define ESP32

#include "async_server.h"
#include <ESPAsyncWebServer.h>

extern AsyncWebServer g_asyncServer(80);

void MyServer2::loop()
{
}

void MyServer2::setup()
{
    Serial.println("setup");
    g_asyncServer.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/plain", "Hello World");
        });
    g_asyncServer.begin();
}

#endif