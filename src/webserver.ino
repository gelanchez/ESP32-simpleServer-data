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

#include <Arduino.h>
#include "constants.h"
#include <WiFi.h>

#include "async_server.h"
#include "simple_server.h"

void setup()
{
    Serial.begin(115200);
    delay(1000);

    pinMode(Constants::ledPin, OUTPUT);

    /**
     * @brief Connect to WiFi.
     */
    WiFi.config(Constants::ip, Constants::gateway, Constants::subnet);
    WiFi.begin(Constants::ssid, Constants::password);
    while (WiFi.status() != WL_CONNECTED)
        delay(1000);
    Serial.print("Connected to WiFi ");
    Serial.print(Constants::ssid);
    Serial.print(" as ");
    Serial.println(WiFi.localIP());

    /**
     * @brief Server setup.
     */
    if (Constants::serverType == ServerType::SIMPLE_WEBSERVER)
        MySimpleServer::setup();
    else if (Constants::serverType == ServerType::ASYNC_WEBSERVER)
        MyAsyncServer::setup();
    
}

void loop()
{
    if (Constants::serverType == ServerType::SIMPLE_WEBSERVER)
        MySimpleServer::loop();
    else if (Constants::serverType == ServerType::ASYNC_WEBSERVER)
        MyAsyncServer::loop();
}