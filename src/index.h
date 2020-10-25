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
 * @brief main.html, main.js and styles.css in one char array.
 */
const char MAIN_page[] PROGMEM = R"=====(

<!DOCTYPE html>
<html lang="en">

<head>
    <title>ESP32-simpleServer-data</title>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
    <meta name="description" content="ESP32 simple webserver data sensor">
    <meta name="author" content="José Ángel Sánchez">
    <link rel="icon" href="data:;base64,iVBORw0KGgo=">
    <style>
        html {
            text-align: center;
            font-family: Arial, Helvetica, sans-serif;
        }

        #title {
            margin: 0px auto;
            text-decoration: underline;
        }

        #data {
            margin: 5px auto;
        }

        #led {
            margin-bottom: -20px;
        }
    </style>
</head>

<body>
    <h2 id="title">ESP32 simple server with AJAX</h2>
    <p id="data">
        <button id="ledButton" onclick="changeLed()">Toggle LED</button>
        <canvas id="led" width="50" height="50"></canvas>
        <span>SENSORS: Temperature: </span><span id="temperature">0</span><span>°C. Illuminance: </span><span
            id="illuminance">0</span><span> lx.</span>
    </p>

    <div class="chart-container" style="position: relative; width:95vw; margin:auto">
        <canvas id="temperatureChart" width="800" height="200" aria-label="Temperature chart" role="img"></canvas>
    </div>
    <br>
    <div class="chart-container" style="position: relative; width:95vw; margin:auto">
        <canvas id="illuminanceChart" width="800" height="200" aria-label="Illuminance chart" role="img"></canvas>
    </div>

    <script src="https://code.jquery.com/jquery-3.5.1.min.js"
        integrity="sha256-9/aliU8dGd2tb6OSsuzixeV4y/faTqgFtohetphbbj0=" crossorigin="anonymous"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/Chart.js/2.9.3/Chart.js"
        integrity="sha512-QEiC894KVkN9Tsoi6+mKf8HaCLJvyA6QIRzY5KrfINXYuP9NxdIkRQhGq3BZi0J4I7V5SidGM3XUQ5wFiMDuWg=="
        crossorigin="anonymous"></script>
    <script type="text/javascript">
        var counter = 0;

        // Draw LED
        var contextLED = document.getElementById("led").getContext("2d");
        contextLED.arc(25, 25, 15, 0, Math.PI * 2, false);
        contextLED.lineWidth = 3;
        contextLED.strokeStyle = "black";
        contextLED.fillStyle = "black";
        contextLED.stroke();
        contextLED.fill();

        var ctxTemp = document.getElementById('temperatureChart').getContext('2d');
        var temperatureChart = new Chart(ctxTemp, {
            type: 'line',
            data: {
                //labels: [1, 2, 3],
                datasets: [{
                    label: 'Temperature',
                    borderColor: 'red',
                    backgroundColor: 'red',
                    borderWidth: 2,
                    pointRadius: 1,
                    fill: false
                }]
            },
            options: {
                legend: {
                    display: false
                },
                responsive: true,
                scales: {
                    xAxes: [{
                        display: true,
                        ticks: {
                            display: true
                        }
                    }],
                    yAxes: [{
                        display: true,
                        scaleLabel: {
                            display: true,
                            labelString: 'Temperature (ºC)'
                        },
                        ticks: {
                            min: 0,
                            max: 40
                        }
                    }]
                },
                showLines: true,
                elements: {
                    line: {
                        tension: 0  // disables bezier curves
                    }
                },
                animation: {
                    duration: 0  // general animation time
                },
                hover: {
                    animationDuration: 0  // duration of animations when hovering an item
                },
                responsiveAnimationDuration: 0  // animation duration after a resize
            }
        });

        var ctxIllum = document.getElementById('illuminanceChart').getContext('2d');
        var illuminanceChart = new Chart(ctxIllum, {
            type: 'line',
            data: {
                datasets: [{
                    label: 'Illuminance',
                    borderColor: 'gold',
                    backgroundColor: 'gold',
                    borderWidth: 2,
                    pointRadius: 1,
                    fill: false
                }]
            },
            options: {
                legend: {
                    display: false
                },
                responsive: true,
                scales: {
                    xAxes: [{
                        display: true,
                        ticks: {
                            display: true
                        }
                    }],
                    yAxes: [{
                        display: true,
                        scaleLabel: {
                            display: true,
                            labelString: 'Illuminance (lux)'
                        },
                        ticks: {
                            min: 0,
                            max: 10000
                        }
                    }]
                },
                showLines: true,
                animation: {
                    duration: 0  // general animation time
                },
                hover: {
                    animationDuration: 0  // duration of animations when hovering an item
                },
                responsiveAnimationDuration: 0  // animation duration after a resize
            }
        });

        function changeLed() {
            $.ajax({
                type: "post",
                url: "/changeled",
                data: {},
                complete: function () {
                    getLedStatus();
                }
            });
        }
        function getLedStatus() {
            $.ajax({
                url: "/_led_status",
                dataType: "json",
                success: function (data) {
                    // const jsondata = JSON.parse(data);  // Not necessary as AJAX dataType is json
                    if (data.ledStatus == true) {
                        updateLED(true);
                    }
                    else {
                        updateLED(false);
                    }
                }
            });
        }
        function updateLED(ledStatus) {
            if (ledStatus) {
                contextLED.fillStyle = "red";
                contextLED.fill();
            }
            else {
                contextLED.fillStyle = "black";
                contextLED.fill();
            }
        }

        function updateValues() {
            $.ajax({
                url: "/_sensors",
                dataType: "json",
                success: function (data) {
                    document.getElementById("temperature").innerHTML = data.temperature;
                    document.getElementById("illuminance").innerHTML = data.illuminance;
                    updateCharts(data.temperature, data.illuminance);
                }
            });
        }

        function updateCharts(temperature, illuminance) {
            let date = new Date();
            let timeDislpayed = date.getMinutes().toString().padStart(2, '0') + ":" + date.getSeconds().toString().padStart(2, '0');
            addData(temperatureChart, timeDislpayed, [temperature]);
            addData(illuminanceChart, timeDislpayed, [illuminance]);
            // Remove values from chart after 100 data
            if (counter < 100) {
                counter++;
            }
            else {
                removeData(temperatureChart);
                removeData(illuminanceChart);
            }
        }

        function addData(chart, label, data) {
            chart.data.labels.push(label);
            chart.data.datasets.forEach((dataset) => {
                dataset.data.push(data);
            });
            chart.update();
        }

        function removeData(chart) {
            chart.data.labels.shift();
            chart.data.datasets.forEach((dataset) => {
                dataset.data.shift();
            });
            chart.update();
        }

        window.setInterval(updateValues, 2000);
    </script>
</body>

</html>

)=====";

#endif