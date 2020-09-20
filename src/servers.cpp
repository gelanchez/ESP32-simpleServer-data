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
#include <WiFi.h>

ParentServer::ParentServer()
{
    if (Constants::serverType == ServerType::SIMPLE_WEBSERVER)
        SimpleServer();
    else if (Constants::serverType == ServerType::ASYNC_WEBSERVER)
        AsyncServer();
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


SimpleServer::SimpleServer()
{
}

SimpleServer::~SimpleServer()
{
}

void SimpleServer::setup()
{

}

void SimpleServer::loop()
{

}

AsyncServer::AsyncServer()
{
}

AsyncServer::~AsyncServer()
{
}

void AsyncServer::setup()
{

}

void AsyncServer::loop()
{

}