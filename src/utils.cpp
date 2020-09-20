/**
 * @file utils.cpp
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Useful methods.
 * @version 0.0.1
 * @date 2020-09-15
 * @copyright GPL-3.0
 */

#include "constants.h"
#include "utils.h"
#include <WiFi.h>

void Utils::wifiConnect()
{
    WiFi.config(Constants::ip, Constants::gateway, Constants::subnet);
    WiFi.begin(Constants::ssid, Constants::password);
    while (WiFi.status() != WL_CONNECTED)
        delay(1000);
    Serial.print("Connected to WiFi ");
    Serial.print(Constants::ssid);
    Serial.print(" as ");
    Serial.println(WiFi.localIP());
}