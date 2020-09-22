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

#include <ArduinoJson.h>
#include "constants.h"
#include "index.h"  // HTML webpage contents with javascripts
#include "mysensors.h"
#include "servers.h"
#include <WebServer.h>

bool ledStatus(LOW);
StaticJsonDocument<150> ledJson;

WebServer server(80);

ParentServer webserver = ParentServer();

void setup()
{
    Serial.begin(115200);
    delay(1000);

    webserver.wifiConnect();

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
    server.send(200, "text/html", MAIN_page_simple);
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