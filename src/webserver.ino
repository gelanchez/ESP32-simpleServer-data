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
#include <WebServer.h>
#include <WiFi.h>

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
    g_server.on("", handle_notFound);
    g_server.on("/", handle_notFound);
    g_server.on("/changeled", handle_notFound);
    g_server.on("/_led_status", handle_notFound);
    g_server.begin();
 
}

void loop()
{
    g_server.handleClient();
}

void handle_notFound()
{
    g_server.send(404, "text/plain", "Not found simple");
}

void handle_hello()
{
    g_server.send(200, "text/plain", "Hello simple");
}