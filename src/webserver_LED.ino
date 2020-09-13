/**
 * @file webserver-LED.ino
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Using WebServer, a LED can be switched on and off from the client.
 * @version 0.0.1
 * @date 2020-09-06
 * @copyright GPL-3.0
 */

#include "constants.h"
#include "index_LED.h"
#include <WebServer.h>
#include <WiFi.h>

bool ledStatus(LOW);

WebServer server(80);

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

    server.onNotFound(handle_notFound);
    server.on("", handle_index);
    server.on("/", handle_index);
    server.on("/changeled", handle_changeled);

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
    server.send(200, "text/html", MAIN_LED);
}

void handle_changeled()
{
    ledStatus = !ledStatus;
}