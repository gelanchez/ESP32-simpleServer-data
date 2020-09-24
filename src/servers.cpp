/**
 * @file servers.cpp
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief 
 * @version 0.0.1
 * @date 2020-09-20
 * @copyright GPL-3.0
 */

#include "constants.h"
#include "servers.h"
#include <WebServer.h>
#include <WiFi.h>

ParentServer::ParentServer()
{
}

ParentServer::~ParentServer()
{
}

void ParentServer::setup()
{
}

void ParentServer::loop()
{
}

/**
 * @brief WiFi network connection
 */
void ParentServer::wifiConnect()
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

// Static initialization
WebServer SimpleServer::s_wserver(80);

SimpleServer::SimpleServer()
{
}

SimpleServer::~SimpleServer()
{
}

void SimpleServer::handle_notFound()
{
    s_wserver.send(404, "text/plain", "Not found");
}

void SimpleServer::setup()
{
    Serial.println("simple setup");
    s_wserver.onNotFound(SimpleServer::handle_notFound);

    s_wserver.begin();
}

void SimpleServer::loop()
{
    Serial.println("simple loop");
    s_wserver.handleClient();
}

AsyncServer::AsyncServer()
{
}

AsyncServer::~AsyncServer()
{
}

void AsyncServer::setup()
{
    Serial.println("async setup");
}

void AsyncServer::loop()
{
    Serial.println("async loop");
}