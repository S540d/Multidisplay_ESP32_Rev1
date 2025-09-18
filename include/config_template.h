#ifndef CONFIG_PRIVATE_H
#define CONFIG_PRIVATE_H

// ============================================================================
// CONFIG TEMPLATE - Kopiere diese Datei zu 'config_private.h' und fülle die Werte aus
// ============================================================================
// WICHTIG: config_private.h ist bereits in .gitignore und wird NICHT ins Repository übertragen!
// Diese Template-Datei dient als Vorlage für andere Entwickler.

// WiFi Konfiguration
const char* ssid = "IhrWLANName";          // Name des WLAN-Netzwerks
const char* password = "IhrWLANPasswort";  // WLAN-Passwort

// MQTT Broker Konfiguration
const char* mqtt_server = "192.168.1.100"; // IP-Adresse des MQTT Brokers
const int mqtt_port = 1883;                // MQTT Port (Standard: 1883)
const char* mqtt_user = "";                // MQTT Benutzername (leer wenn nicht benötigt)
const char* mqtt_pass = "";                // MQTT Passwort (leer wenn nicht benötigt)

// Optional: Weitere MQTT Einstellungen
// const char* mqtt_client_id = "esp32_display";
// const char* mqtt_status_topic = "home/display/status";
// const int mqtt_keepalive = 60;
// const bool mqtt_retain = false;

#endif