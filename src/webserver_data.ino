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

#include "utils.h"

void setup()
{
    Serial.begin(115200);
    delay(1000);

    Utils::wifiConnect();


}

void loop()
{

}

#endif