/**
 * @file webserver.ino
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Main implementation of the webserver to control a LED and present
 * data from the sensors to the clients. Two webservers and technologies can
 * be used:
 * a) Simple webserver + jQuery AJAX.
 * b) Async webserver + websockets.
 * @version 0.0.1
 * @date 2020-09-20
 * @copyright GPL-3.0
 */

#include "constants.h"
#include "servers.h"

SimpleServer simpleServer;
AsyncServer asyncServer;

ParentServer *pServer = nullptr;

void setup()
{
    Serial.begin(115200);
    delay(1000);

    pinMode(Constants::ledPin, OUTPUT);

    ParentServer::wifiConnect();
    
    if (Constants::serverType == ServerType::SIMPLE_WEBSERVER)
        pServer = &simpleServer;
    else if (Constants::serverType == ServerType::ASYNC_WEBSERVER)
        pServer = &asyncServer;

    pServer->setup();
}

void loop()
{
    pServer->loop();
}