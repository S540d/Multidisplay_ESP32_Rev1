#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include "config_private.h"

// MQTT Topics
const char* topic1 = "home/PV/Share_renewable";
const char* topic2 = "home/PV/EnergyPrice";
const char* topic3 = "home/PV/WallboxPower";
const char* topic4 = "home/PV/chargingLevel";
const char* topic5 = "home/Heating/WaterTemperature";
const char* topic6 = "home/stocks/CL2PACurr";
const char* topic7 = "home/calendar/next";

// Global variables
float Numtopic1 = 0, Numtopic1_old = 0;
float Numtopic2 = 0, Numtopic2_old = 0;
float Numtopic3 = 0, Numtopic3_old = 0;
float Numtopic4 = 0, Numtopic4_old = 0;
float Numtopic5 = 0, Numtopic5_old = 0;
float currentPrice = 0, currentPrice_old = 0;
float refPrice = 0;
String lastEvent = "";

// Anti-Burn-In
int baseX = 10;
int baseY = 5;
int offsetX = 0;
int dir = 1;
unsigned long lastShift = 0;
const unsigned long shiftInterval = 60000; // 60 seconds
unsigned long lastRefresh = 0;
const unsigned long refreshInterval = 1000; // Value check interval

// TFT and MQTT
TFT_eSPI tft = TFT_eSPI();
WiFiClient espClient;
PubSubClient client(espClient);

// Helper function
float parseAndRound(String msg) {
  return round(msg.toFloat() * 10) / 10.0;
}

// Trend color
uint16_t getTrendColor(float val, float oldVal, bool invert=false) {
  if (val == 0.0) return TFT_WHITE;
  if (invert) return (val < oldVal) ? TFT_GREEN : TFT_RED;
  return (val > oldVal) ? TFT_GREEN : TFT_RED;
}

// Anti-Burn-In update
void updateOffset() {
  if (millis() - lastShift > shiftInterval) {
    offsetX += dir;
    if (offsetX > 3) dir = -1;
    if (offsetX < -3) dir = 1;
    lastShift = millis();
  }
}

// WiFi
void setup_wifi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);
}

// MQTT Callback
void callback(char* topic, byte* payload, unsigned int length) {
  String msg;
  for (unsigned int i = 0; i < length; i++) msg += (char)payload[i];

  if (String(topic) == topic7) {
    StaticJsonDocument<200> doc;
    if (deserializeJson(doc, msg) == DeserializationError::Ok) {
      if (doc.containsKey("event")) lastEvent = doc["event"].as<String>();
    }
  } 
  else if (String(topic) == topic6) {
    StaticJsonDocument<300> doc;
    if (deserializeJson(doc, msg) == DeserializationError::Ok) {
      if (doc.containsKey("current") && doc.containsKey("ref")) {
        currentPrice = doc["current"];
        refPrice = doc["ref"];
      }
    }
  } 
  else {
    float val = parseAndRound(msg);
    if (String(topic) == topic1) Numtopic1 = val;
    else if (String(topic) == topic2) Numtopic2 = val;
    else if (String(topic) == topic3) Numtopic3 = val;
    else if (String(topic) == topic4) Numtopic4 = val;
    else if (String(topic) == topic5) Numtopic5 = val;
  }
}

// MQTT reconnect
void reconnect() {
  while (!client.connected()) {
    if (client.connect("ESP32Client", mqtt_user, mqtt_pass)) {
      client.subscribe(topic1);
      client.subscribe(topic2);
      client.subscribe(topic3);
      client.subscribe(topic4);
      client.subscribe(topic5);
      client.subscribe(topic6);
      client.subscribe(topic7);
    } else delay(5000);
  }
}

// Draw values
void drawValue(int y, const char* label, float val, float oldVal, bool hasAmpel=false, bool invertTrend=false) {
  float displayVal = isnan(val) ? 0 : val;
  float displayOld = isnan(oldVal) ? displayVal : oldVal;

  uint16_t color = getTrendColor(displayVal, displayOld, invertTrend);

  tft.fillRect(baseX + offsetX, baseY + y, 240, 20, TFT_BLACK);

  // Traffic light / Label
  uint16_t labelColor = TFT_WHITE;
  if (hasAmpel) {
    if (displayVal < 30) labelColor = TFT_RED;
    else if (displayVal < 70) labelColor = TFT_YELLOW;
    else labelColor = TFT_GREEN;
  }

  tft.setTextColor(labelColor, TFT_BLACK);
  tft.setCursor(baseX + offsetX, baseY + y);
  tft.print(label);

  tft.setTextColor(color, TFT_BLACK);
  tft.setCursor(baseX + offsetX + 160, baseY + y);
  tft.printf("%.1f", displayVal);

  if (hasAmpel) {
    tft.fillCircle(baseX + offsetX + 260, baseY + y + 8, 5, labelColor);
  }
}

// CPU + LDR
void drawCPUandLDR() {
  tft.setTextSize(1);
  float cpu = (float)ESP.getFreeHeap() / (float)ESP.getHeapSize();
  int cpuLoad = int((1.0 - cpu) * 100);
  int ldrValue = analogRead(34);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setCursor(baseX, 230);
  tft.printf("CPU:%d%%  LDR:%d", cpuLoad, ldrValue);
  tft.setTextSize(2);
}

// Setup
void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(2);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setCursor(0, 0);
  tft.println("Starting...");
  delay(100);
  tft.fillScreen(TFT_BLACK);

// LDR
  analogReadResolution(12);            // 12 bit resolution: 0–4095
  analogSetAttenuation(ADC_11db);      // Full input voltage 0–3.3V

}

// Loop
void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  updateOffset();

  // Refresh only on value change or Anti-Burn-In
  if ((Numtopic1 != Numtopic1_old) || (Numtopic2 != Numtopic2_old) || 
      (Numtopic3 != Numtopic3_old) || (Numtopic4 != Numtopic4_old) || 
      (Numtopic5 != Numtopic5_old) || (currentPrice != currentPrice_old) || 
      (millis() - lastShift < 100)) 
  {
    drawValue(0, "OE_Strom%:", Numtopic1, Numtopic1_old, true);
    drawValue(30, "Strompreis:", Numtopic2, Numtopic2_old, false, true);
    drawValue(60, "Wallbox:", Numtopic3, Numtopic3_old);
    drawValue(90, "Charge Lev:", Numtopic4, Numtopic4_old);
    drawValue(120, "Temp H2O:", Numtopic5, Numtopic5_old);
    drawValue(150, "Stock:", currentPrice, currentPrice_old);

    // Event
    tft.fillRect(baseX + offsetX, baseY + 170, 240, 16, TFT_BLACK);
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    tft.setCursor(baseX + offsetX, baseY + 170);
    tft.print(lastEvent);

    drawCPUandLDR();

    // Save old values
    Numtopic1_old = Numtopic1;
    Numtopic2_old = Numtopic2;
    Numtopic3_old = Numtopic3;
    Numtopic4_old = Numtopic4;
    Numtopic5_old = Numtopic5;
    currentPrice_old = currentPrice;
  }
}
 