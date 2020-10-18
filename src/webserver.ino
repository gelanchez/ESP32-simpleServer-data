/**
 * @file webserver.ino
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Main implementation of the simple webserver to control a LED and present
 * data from the sensors to the clients using jQuery AJAX.
 * @version 0.0.1
 * @date 2020-09-29
 * @copyright GPL-3.0
 */

#include <Arduino.h>
#include <ArduinoJson.h>
#include "constants.h"
#include "index.h"
#include <WebServer.h>
#include <WiFi.h>

bool g_ledStatus(LOW);
StaticJsonDocument<100> g_ledJson;

WebServer g_server(80);

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
    g_server.onNotFound(handle_notFound);
    g_server.on("/hello", handle_hello);
    g_server.on("", handle_index);
    g_server.on("/", handle_index);
    g_server.on("/changeled", handle_changeLed);
    g_server.on("/_led_status", handle_ledStatus);
    g_server.begin();
}

void loop()
{
    g_server.handleClient();

    if (g_ledStatus)
        digitalWrite(Constants::ledPin, HIGH);
    else
        digitalWrite(Constants::ledPin, LOW);
}

void handle_notFound()
{
    g_server.send(404, "text/plain", "Not found");
}

void handle_hello()
{
    g_server.send(200, "text/plain", "Hello world");
}

void handle_index()
{
    g_server.send(200, "text/html", MAIN_page);
}

void handle_changeLed()
{
    g_ledStatus = !g_ledStatus;
}

void handle_ledStatus()
{
    String output;
    g_ledJson["ledStatus"] = g_ledStatus;
    serializeJson(g_ledJson, output);
    g_server.send(200, "text/json", output);
}