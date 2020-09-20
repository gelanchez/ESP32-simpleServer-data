/**
 * @file index.h
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief HTML with the main pages for the servers.
 * @version 0.0.1
 * @date 2020-09-20
 * @copyright GPL-3.0
 */

#ifndef INDEX_H
#define INDEX_H

/**
 * @brief Main html page for the SIMPLE_WEBSERVER.
 */
const char MAIN_page_simple[] PROGMEM = R"=====(

<!DOCTYPE html>
<html lang="en">

<head>
    <!-- Required meta tags -->
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">

    <!-- Bootstrap CSS -->
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.5.2/css/bootstrap.min.css"
        integrity="sha384-JcKb8q3iqJ61gNV9KGb8thSsNjpSL0n8PARn9HuZOnIxN0hoP+VmmDGMN5t9UJ0Z" crossorigin="anonymous">

    <title>ESP32 WiFi LED control</title>
</head>

<body>
    <h4>ESP32 LED control</h4>

    <input id ="ledbutton" class="btn btn-dark btn-lg" type="submit" value="Switch LED on" onclick="changeLed();">

    <!-- Optional JavaScript -->
    <!-- jQuery first, then Popper.js, then Bootstrap JS -->
    <!-- Not using the jQuery slim version as it doesn't have AJAX-->
    <script src="https://code.jquery.com/jquery-3.5.1.min.js"
        integrity="sha256-9/aliU8dGd2tb6OSsuzixeV4y/faTqgFtohetphbbj0="
        crossorigin="anonymous"></script>
    <script src="https://cdn.jsdelivr.net/npm/popper.js@1.16.1/dist/umd/popper.min.js"
        integrity="sha384-9/reFTGAW83EW2RDu2S0VKaIzap3H66lZH81PoYlFhbGU+6BZp6G7niu735Sk7lN"
        crossorigin="anonymous"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.5.2/js/bootstrap.min.js"
        integrity="sha384-B4gt1jrGC7Jh4AgTPSdUtOBvfO8shuf57BaghqFfPlYxofvL8/KUEfYiJOMMV+rV"
        crossorigin="anonymous"></script>
    <script type="text/javascript">
        function changeLed(){
            $.ajax({
                type: "post",
                url: "/changeled",
                data: {},
                complete: function(){
                    getLedStatus();
                }
            });
        }
        function getLedStatus(){
            $.ajax({
                url: "/_led_status",
                dataType: "json",
                success: function(data){
                    // const jsondata = JSON.parse(data);  // Not necessary as AJAX dataType is json
                    if (data.ledStatus == true){
                        updateButton(true);
                    }
                    else {
                        updateButton(false);
                    }
                }
            });
        }
        function updateButton(ledStatus){
            if (ledStatus){
                document.getElementById("ledbutton").className = "btn btn-warning btn-lg";
                document.getElementById("ledbutton").value = "Switch LED off";
            }
            else {
                document.getElementById("ledbutton").className = "btn btn-dark btn-lg";
                document.getElementById("ledbutton").value = "Switch LED on";
            }
        }
    </script>
</body>

</html>

)=====";



/**
 * @brief Main html page for the ASYNC_WEBSERVER
 */
const char MAIN_page_async[] PROGMEM = R"=====(



)=====";

#endif