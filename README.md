# CovPrev - Autonomous COVID-19 Symptom Testing And Sanitization Unit With Cross-Platform App

March, 2021 | Project for Microcontrollers and Applications course in SY BTech.

[CovPrev - Autonomous COVID-19 Symptom Testing And Sanitization Unit](#covprev---autonomous-covid-19-symptom-testing-and-sanitization-unit)

  * [Introduction](#introduction)
  * [System Overview](#system-overview)
  * [Data Management and Quasar VueJS App](#data-management-and-quasar-vuejs-app)
  * [Hardware Demonstration](#hardware-demonstration)
  * [Group Details](#group-details)

## Introduction

In the unprecedented times of the COVID-19 pandemic, we all have found social distancing, regular temperature checks and sanitization to be quintessential in order to break the cycle. We recognized this problem and aimed to create a lost cost easily replicable unit based on an Arduino Uno and an ESP8266 Module.

The primary symptoms a COVID-19 patient shows is a high body temperature and a low SpO₂ level in the blood. These are easily measurable parameters using the appropriate sensors. Based on this knowledge, we worked on **CovPrev**, a device which can be deployed at the entrance of malls, hospitals, offices and other high footfall public places. It is a four subsystem device consisting of:

1. Sanitization Spray 
2. Thermometer and Pulse Oximeter Sensors
3. Data Storage, Analysis and Accessibility Through Cross Platform App

*My individual contribution to the project was in primarily part three, the data subsystem.*



## System Overview

The system's main function is to provide cheap accurate multifunctionality which can be deployed at various locations easily. When a user approaches the device, an IR triggered sanitizer spray ensures hygiene in the process. Then, the user is prompted to place their index finger on a sensor assembly equipped with a [MAX30100 Pulse Oximeter and Heart-Rate Sensor](https://datasheets.maximintegrated.com/en/ds/MAX30100.pdf) and a [MLX90614 Infra Red Thermometer](https://www.sparkfun.com/datasheets/Sensors/Temperature/MLX90614_rev001.pdf), which are interfaced to an [Arduino Uno](https://store.arduino.cc/usa/arduino-uno-rev3) development board. The user's temperature and oxygen level are taken, and if the values are in a given range, then the user is allowed to proceed into the building or room. If the readings aren't in the range, the user is notified so using a buzzer and LEDs. The data taken from the sensors interfaced to the Arduino Uno are sent to a [ESP-8266 NodeMCU](https://cdn-shop.adafruit.com/product-files/2471/0A-ESP8266__Datasheet__EN_v4.3.pdf) module via serial communication. This module then stores the data either online on the Firebase Realtime Database or offline on a microSD card based on the internet connection availability.
![](https://github.com/anwaypimpalkar/autonomousCovidSymptomTestingUnit/raw/main/misc/Overall%20Block%20Diagram.png)



## Data Management and Quasar VueJS App

This subsystem was my primary responsibility and contribution to the project. 

To fulfill my purposes, I chose to use the cheap and readily available ESP-8266 NodeMCU development board with a built-in Wi-Fi module for internet connectivity. The data was stored and sent to the cloud for easy user access. 

![](https://github.com/anwaypimpalkar/autonomousCovidSymptomTestingUnit/raw/main/misc/Data%20Subsystem%20Block%20Diagram.png)

For storing the incoming sensor data from the Arduino Uno, I created two channels - online and offline storage:

- **Online Storage:** In the presence of a connection to the internet, the data was sent to a Google Firebase Realtime Database. This was chosen because of the low latency and cross-platform API availability. The sensor data was stored in the database by using the APIs provided using the [Firebase-ESP8266 library](https://github.com/mobizt/Firebase-ESP8266).
- **Offline Storage:** To facilitate the storage of data even in the absence of a stable internet connection, I interfaced a microSD card to the ESP8266 using a [HW-125 card reader](https://datasheet.octopart.com/32312-Parallax-datasheet-13552938.pdf). Whenever the internet connection resumed, the offline data is synced to online database.

To make the data easily accessible, I built an app on the [VueJS Quasar Framework ](https://quasar.dev/). On a high-level, the app has the following features:

- **Tabular Data Overview:** All the data uploaded to the Firebase database is displayed reverse chronologically in a tabular fashion on the home screen of the app. The data is retrieved from the database using the provided [Firebase JavaScript SDK](https://firebase.google.com/docs/reference/js).
- **Graphical Analytics:** To analyze data trends with more ease, the home screen also contains graphical representations of all the datasets individually. This was executed using the [ApexCharts.js](https://apexcharts.com/) library.
- **Device Online/Offline Status (KeepAlive System):** The ESP8266 sends a KeepAlive message to Firebase every 5 seconds when the device is online. It is immediately reflected in the app as well. If the device misses 3 such KeepAlive pings, the device status changes to offline.
- **View Device Sensor Health:** If a particular sensor malfunctions on the Arduino Uno, the ESP8266 updates the database about the sensor error for the user to check. 
- **Update Acceptable Sensor Reading Parameters:** Through the app, users are able to change the acceptable values of the on-board sensors which decide whether a given user is within the acceptable SpO₂ and temperature ranges. 
- **View Basic Overview of Project:** A page including the project details, links and references is also added to the app.

![](https://github.com/anwaypimpalkar/autonomousCovidSymptomTestingUnit/raw/main/misc/App%20Screenshots%201.png)

![](https://github.com/anwaypimpalkar/autonomousCovidSymptomTestingUnit/raw/main/misc/App%20Screenshots%202.png)

![](https://github.com/anwaypimpalkar/autonomousCovidSymptomTestingUnit/raw/main/misc/Firebase%20Screenshot.png)

## Hardware Demonstration

The hardware required was implemented in a makeshift manner as a proof of concept for the evaluation of the project.  An unnarrated [video demonstration](https://youtu.be/aAD6R5BNwCo) has been documented. The [presentation slides](https://github.com/anwaypimpalkar/autonomousCovidSymptomTestingUnit/raw/main/misc/CovPrev%20Presentation%20Slides.pdf) of this project are also made available.

![Hardware Assembly](https://github.com/anwaypimpalkar/autonomousCovidSymptomTestingUnit/raw/main/misc/Hardware%20Assembly.png)

## Group Details

This project was created by a group of 5 students: Kushagra Shrivastava, Shubham Mujumdar, Esha Dorle, Ishita Rathor and myself - all second year students in the Electronics and Telecommunications Department at College of Engineering, Pune.
