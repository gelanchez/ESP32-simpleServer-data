/**
 * @file async_server.cpp
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Async webserver + websockets.
 * @version 0.0.1
 * @date 2020-09-27
 * @copyright GPL-3.0
 */

#define ESP32
#include "async_server.h"
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

extern AsyncWebServer g_asyncServer(80);

void MyAsyncServer::loop()
{
}

void MyAsyncServer::setup()
{
    g_asyncServer.on("/hello", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/plain", "Hello async");
        });
    g_asyncServer.onNotFound([](AsyncWebServerRequest *request){
        request->send(404, "text/plain", "Not found async");
    });
    g_asyncServer.begin();
}