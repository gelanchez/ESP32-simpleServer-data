/**
 * @file simple_server.cpp
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Simple webserver + jQuery AJAX.
 * @version 0.0.1
 * @date 2020-09-26
 * @copyright GPL-3.0
 */

#include "simple_server.h"
#include <WebServer.h>

extern WebServer g_simpleServer(80);

void MySimpleServer::handle_notFound()
{
    g_simpleServer.send(404, "text/plain", "Not found simple");
}

void MySimpleServer::loop()
{
    g_simpleServer.handleClient();
}

void MySimpleServer::setup()
{
    g_simpleServer.onNotFound(MySimpleServer::handle_notFound);
    g_simpleServer.on("", MySimpleServer::handle_notFound);
    g_simpleServer.on("/", MySimpleServer::handle_notFound);
    g_simpleServer.on("/changeled", MySimpleServer::handle_notFound);
    g_simpleServer.on("/_led_status", MySimpleServer::handle_notFound);
    g_simpleServer.begin();
}