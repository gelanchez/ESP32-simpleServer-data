/**
 * @file simple_server.h
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Simple webserver + jQuery AJAX.
 * @version 0.0.1
 * @date 2020-09-26
 * @copyright GPL-3.0
 */

#ifndef SIMPLE_SERVER_H
#define SIMPLE_SERVER_H

namespace MySimpleServer
{
    void handle_notFound();
    void handle_hello();
    void loop();
    void setup();
}

#endif