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

class Server
{
    private:
    protected:
    public:
        Server();
        ~Server();
        virtual void setup();
        virtual void loop();
        void wifiConnect();
};


class SimpleServer: public Server
{
    private:
    protected:
    public:
        SimpleServer();
        ~SimpleServer();
        virtual void setup();
        virtual void loop();
};


class AsyncServer: public Server
{
    private:
    protected:
    public:
        AsyncServer();
        ~AsyncServer();
        virtual void setup();
        virtual void loop();

};

#endif