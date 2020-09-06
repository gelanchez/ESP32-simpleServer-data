/**
 * @file webserver-LED.ino
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Using WebServer, a LED can be switched on and off from the client.
 * @version 0.0.1
 * @date 2020-09-06
 * @copyright GPL-3.0
 */

#include "constants.h"

void setup()
{
    pinMode(Constants::ledPin, OUTPUT);
}

void loop()
{
    digitalWrite(Constants::ledPin, HIGH);
    delay(1000);
    digitalWrite(Constants::ledPin, LOW);
    delay(1000);
}