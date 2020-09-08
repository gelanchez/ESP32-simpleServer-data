/**
 * @file webserver-LED.ino
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Using WebServer, a LED can be switched on and off from the client.
 * @version 0.0.1
 * @date 2020-09-06
 * @copyright GPL-3.0
 */

#include "constants.h"
#include <WiFi.h>

void setup()
{
    Serial.begin(115200);
    delay(1000);

    WiFi.config(Constants::ip, Constants::gateway, Constants::subnet);
    WiFi.begin(Constants::ssid, Constants::password);
    while(WiFi.status() != WL_CONNECTED)
        delay(1000);
    Serial.print("Connected to WiFi ");
    Serial.print(Constants::ssid);
    Serial.print(" as ");
    Serial.println(WiFi.localIP());

    pinMode(Constants::ledPin, OUTPUT);
}

void loop()
{
    digitalWrite(Constants::ledPin, HIGH);
    delay(1000);
    digitalWrite(Constants::ledPin, LOW);
    delay(1000);
}