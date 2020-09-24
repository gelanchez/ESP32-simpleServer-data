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

ParentServer webserver;

void setup()
{
    Serial.begin(115200);
    delay(1000);

    pinMode(Constants::ledPin, OUTPUT);

    if (Constants::serverType == ServerType::SIMPLE_WEBSERVER)
        webserver = SimpleServer();
    else if (Constants::serverType == ServerType::ASYNC_WEBSERVER)
        webserver = AsyncServer();

    webserver.wifiConnect();
    webserver.setup();
}

void loop()
{
    webserver.loop();
}