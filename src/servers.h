/**
 * @file servers.h
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief 
 * @version 0.0.1
 * @date 2020-09-20
 * @copyright GPL-3.0
 */

#ifndef SERVERS_H
#define SERVERS_H

#include "constants.h"
#include <WebServer.h>

class ParentServer
{
    private:
    protected:
    public:
        ParentServer();
        ~ParentServer();
        virtual void setup();
        virtual void loop();
        static void wifiConnect();
};


class SimpleServer: public ParentServer
{
    private:
        static WebServer s_wserver;
    protected:
        static void handle_notFound();
    public:
        SimpleServer();
        ~SimpleServer();
        virtual void setup() override;
        virtual void loop() override;
};


class AsyncServer: public ParentServer
{
    private:
    protected:
    public:
        AsyncServer();
        ~AsyncServer();
        virtual void setup() override;
        virtual void loop() override;

};

#endif