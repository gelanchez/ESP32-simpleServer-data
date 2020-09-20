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

#ifndef ESP32
#define ESP32

#include <ArduinoJson.h>
#include "constants.h"
#include <ESPAsyncWebServer.h>
#include "index.h"  // HTML webpage contents with javascripts
#include "mysensors.h"
#include "servers.h"
#include <WebServer.h>

Photoresistor photoresistor(Constants::photoresistorPin);
Thermistor thermistor(Constants::thermistorPin);


void setup()
{
    Serial.begin(115200);
    delay(1000);

    /**
     * @brief WiFi network connection
     */
    WiFi.config(Constants::ip, Constants::gateway, Constants::subnet);
    WiFi.begin(Constants::ssid, Constants::password);
    while (WiFi.status() != WL_CONNECTED)
        delay(1000);
    Serial.print("Connected to WiFi ");
    Serial.print(Constants::ssid);
    Serial.print(" as ");
    Serial.println(WiFi.localIP());

}

void loop()
{

}



#endif