/**
 * @file webserver_data.ino
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief ESP32 WebServer data real time charts using ESPAsyncWebServer
 * as a websocket server.
 * @version 0.0.1
 * @date 2020-09-16
 * @copyright GPL-3.0
 */

#ifndef ESP32
#define ESP32

#include <ArduinoJson.h>
#include "constants.h"
#include "mysensors.h"
#include "utils.h"

Photoresistor photoresistor(Constants::photoresistorPin);
Thermistor thermistor(Constants::thermistorPin);

StaticJsonDocument<150> doc;

void setup()
{
    Serial.begin(115200);
    delay(1000);

    Utils::wifiConnect();

}

void loop()
{
    static unsigned long lastUpdate = millis();
    if ((millis() - lastUpdate) > 100)
    {
        lastUpdate = millis();
        doc["illuminance"] = photoresistor.read();
        doc["temperature"] = thermistor.read();

        //serializeJson(doc, Serial);
        //Serial.println();

        String output;
        serializeJson(doc, output);
    }
}

#endif