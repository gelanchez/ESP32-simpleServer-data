/**
 * @file webserver_LED.ino
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Using WebServer, a LED can be switched on and off from the client.
 * @version 0.0.1
 * @date 2020-09-06
 * @copyright GPL-3.0
 */

#include <ArduinoJson.h>
#include "constants.h"
#include "index_LED.h"
#include "utils.h"
#include <WebServer.h>

bool ledStatus(LOW);
StaticJsonDocument<150> ledJson;

WebServer server(80);

void setup()
{
    Serial.begin(115200);
    delay(1000);

    Utils::wifiConnect();

    pinMode(Constants::ledPin, OUTPUT);

    server.onNotFound(handle_notFound);
    server.on("", handle_index);
    server.on("/", handle_index);
    server.on("/changeled", handle_changeLed);
    server.on("/_led_status", handle_ledStatus);

    server.begin();
}

void loop()
{
    server.handleClient();

    if (ledStatus)
        digitalWrite(Constants::ledPin, HIGH);
    else
        digitalWrite(Constants::ledPin, LOW);
}

void handle_notFound()
{
    server.send(404, "text/plain", "Not found");
}

void handle_index()
{
    server.send(200, "text/html", MAIN_page);
}

void handle_changeLed()
{
    ledStatus = !ledStatus;
}

void handle_ledStatus()
{
    String output;
    ledJson["ledStatus"] = ledStatus;
    serializeJson(ledJson, output);
    server.send(200, "text/json", output);
}