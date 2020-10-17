/**
 * @file index.h
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief HTML with the main page.
 * @version 0.0.1
 * @date 2020-09-29
 * @copyright GPL-3.0
 */

#ifndef INDEX_H
#define INDEX_H

/**
 * @brief Main html page.
 */
const char MAIN_page[] PROGMEM = R"=====(

<!DOCTYPE html>
<html lang="en">
<head>
    <title>ESP32-simpleServer-data</title>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
    <meta name="author" content="José Ángel">
    <meta name="description" content="ESP32 simple webserver data sensor">
    <link rel="icon" href="data:;base64,iVBORw0KGgo=">
    <style>
        html {text-align: center;}
        #title {
            margin: 0px auto;
            text-decoration: underline;
        }
        #data { margin: 5px auto;}
        #led { margin-bottom: -20px;}
    </style>
</head>
<body>
    <h2 id="title">ESP32 simple server with AJAX</h2>
    <p id="data">
        <button id="ledButton" onclick="changeLed()">Toggle LED</button>
        <canvas id="led" width="50" height="50"></canvas>
    </p>

    <script src="https://code.jquery.com/jquery-3.5.1.min.js" integrity="sha256-9/aliU8dGd2tb6OSsuzixeV4y/faTqgFtohetphbbj0=" crossorigin="anonymous"></script>
    <script type="text/javascript">
        // Draw LED
        var canvasLED = document.getElementById("led");
        var contextLED = canvasLED.getContext("2d");
        contextLED.arc(25, 25, 15, 0, Math.PI * 2, false);
        contextLED.lineWidth = 3;
        contextLED.strokeStyle = "black";
        contextLED.fillStyle = "black";
        contextLED.stroke();
        contextLED.fill();

        function changeLed() {
            $.ajax({
                type: "post",
                url: "/changeled",
                data: {},
                complete: function() {
                    getLedStatus();
                }
            });
        }
        function getLedStatus() {
            $.ajax({
                url: "/_led_status",
                dataType: "json",
                success: function(data) {
                    // const jsondata = JSON.parse(data);  // Not necessary as AJAX dataType is json
                    if (data.ledStatus == true) {
                        updateButton(true);
                    }
                    else {
                        updateButton(false);
                    }
                }
            });
        }
        function updateButton(ledStatus) {
            if (ledStatus){
                contextLED.fillStyle = "red";
                contextLED.fill();
            }
            else {
                contextLED.fillStyle = "black";
                contextLED.fill();
            }
        }
    </script>
</body>
</html>

)=====";

#endif