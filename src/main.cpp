/**
 * Ultrasonic Anemometer Project
 * 
 * Authors: Christopher Höck, Nepomuk Egger
 * Version: 1.0.0
 * Last updated: 2021-09-30
 * 
 * Project Summary:
 * This project aims to develop an ultrasonic anemometer using an ESP32 microcontroller. 
 * Key functionalities include:
 * - Measuring wind speed and direction using ultrasonic sensors.
 * - Monitoring temperature and humidity.
 * - Storing measured data locally on an SD card.
 * - Transmitting data wirelessly (Wi-Fi and Bluetooth).
 * - Supporting NMEA 2000 format for weather and geolocation data transmission.
 * 
 * Project Features:
 * - Modular code architecture for maintainability and scalability.
 * - Integration of NMEA 2000 standard for seamless communication with marine systems.
 * - Flexible configuration for sensor management and data processing.
 **/

#include <Arduino.h>
#include "config.h"
#include "NMEA2000Handler.h"
#include "WirelessHandler.h"
#include "SensorManager.h"
#include "DataHandler.h"

SensorManager sensorManager;
DataHandler dataHandler(0); // Initialisiere mit Laufzeit 0

void initializeSensors() {
    //TODO: Sensoren richtig konfigurieren
    sensorManager.addSensor(ULTRASONIC_SENSOR_1_WRITE_ENABLE, ULTRASONIC_SENSOR_1_READ_ENABLE, 1, OUTPUT, OUTPUT);
    sensorManager.addSensor(ULTRASONIC_SENSOR_2_WRITE_ENABLE, ULTRASONIC_SENSOR_2_READ_ENABLE, 2, OUTPUT, OUTPUT);
    sensorManager.addSensor(ULTRASONIC_SENSOR_3_WRITE_ENABLE, ULTRASONIC_SENSOR_3_READ_ENABLE, 3, OUTPUT, OUTPUT);
    sensorManager.addSensor(ULTRASONIC_SENSOR_4_WRITE_ENABLE, ULTRASONIC_SENSOR_4_READ_ENABLE, 4, OUTPUT, OUTPUT);
    sensorManager.addSensor(ULTRASONIC_SENSOR_CLK, 50, OUTPUT); //TODO: richtig konfigurieren
    sensorManager.addSensor(ULTRASONIC_SENSOR_READ, 51, INPUT); //TODO: richtig konfigurieren
}

void setup() {
    Serial.begin(115200);

    // Initialisierungen
    initNMEA2000();
    initWireless();
    initializeSensors();

    Serial.println("Setup abgeschlossen.");
}

void loop() {
    static double runtime = 300; // Beispielwert, Laufzeit hier simuliert

    // Datenverarbeitung
    PreparedData data = dataHandler.processData(runtime);

    // Daten senden
    sendWirelessData(data);
    sendNMEA2000Data(data);

    delay(1000); // Intervall für die Messungen
}
