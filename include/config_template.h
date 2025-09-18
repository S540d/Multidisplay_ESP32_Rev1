#ifndef CONFIG_PRIVATE_H
#define CONFIG_PRIVATE_H

// WiFi credentials - Please enter your own values and save as config_private.h
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// MQTT broker - Please enter your own values
const char* mqtt_server = "YOUR_MQTT_SERVER_IP";
const int mqtt_port = 1883;
const char* mqtt_user = "YOUR_MQTT_USER";
const char* mqtt_pass = "YOUR_MQTT_PASSWORD";

#endif