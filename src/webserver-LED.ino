/**
 * @file webserver-LED.ino
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Using WebServer, a LED can be switched on and off from the client.
 * @version 0.0.1
 * @date 2020-09-06
 * @copyright GPL-3.0
 */

#include "constants.h"
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
    server.on("/ledon", handle_ledOn);
    server.on("/ledoff", handle_ledOff);

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
    server.send(200, "text/html", sendHTML(ledStatus));
}

void handle_ledOn()
{
    ledStatus = HIGH;
    server.send(200, "text/html", sendHTML(ledStatus));
}

void handle_ledOff()
{
    ledStatus = LOW;
    server.send(200, "text/html", sendHTML(ledStatus));
}

String sendHTML(bool ledStatus)
{
    String str = "<!DOCTYPE html>\n";
    str += "<html>\n";
    str += "<head>\n";
    str += "<meta charset=\"utf-8\">\n";
    str += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1, shrink-to-fit=no\">\n";
    str += "<link rel=\"stylesheet\" href=\"https://stackpath.bootstrapcdn.com/bootstrap/4.5.2/css/bootstrap.min.css\" integrity=\"sha384-JcKb8q3iqJ61gNV9KGb8thSsNjpSL0n8PARn9HuZOnIxN0hoP+VmmDGMN5t9UJ0Z\" crossorigin=\"anonymous\">";
    str += "<title>ESP32 WiFi LED control</title>\n";
    str += "</head>\n";
    str += "<body>\n";
    
    str += "<h4>ESP32 LED control</h4>\n";

    if (ledStatus)
        str +="<a class=\"btn btn-warning btn-lg\" href=\"/ledoff\" role=\"button\">LED ON</a>";
    else
        str +="<a class=\"btn btn-dark btn-lg\" href=\"/ledon\" role=\"button\">LED OFF</a>";

    str += "<script src=\"https://code.jquery.com/jquery-3.5.1.slim.min.js\" integrity=\"sha384-DfXdz2htPH0lsSSs5nCTpuj/zy4C+OGpamoFVy38MVBnE+IbbVYUew+OrCXaRkfj\" crossorigin=\"anonymous\"></script>\n";
    str += "<script src=\"https://cdn.jsdelivr.net/npm/popper.js@1.16.1/dist/umd/popper.min.js\" integrity=\"sha384-9/reFTGAW83EW2RDu2S0VKaIzap3H66lZH81PoYlFhbGU+6BZp6G7niu735Sk7lN\" crossorigin=\"anonymous\"></script>\n";
    str += "<script src=\"https://stackpath.bootstrapcdn.com/bootstrap/4.5.2/js/bootstrap.min.js\" integrity=\"sha384-B4gt1jrGC7Jh4AgTPSdUtOBvfO8shuf57BaghqFfPlYxofvL8/KUEfYiJOMMV+rV\" crossorigin=\"anonymous\"></script>\n";
    
    str +="</body>\n";
    str +="</html>\n";

    return str;
}