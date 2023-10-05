#include "esp_log.h"
#include <Arduino.h>
#include <WiFi.h>
#include <Preferences.h>
#include "WiFiManager.h"
#include "WebServerHandler.h"
#include "NTPClientHandler.h"
#include "DeviceInfoHandler.h"

WiFiManager wifiManager;
WebServerHandler webServerHandler;
NTPClientHandler ntpClientHandler;
DeviceInfoHandler deviceInfoHandler;

void setup() {
  esp_log_level_set("*", ESP_LOG_WARN);  // Ustawia poziom logowania na OSTRZEŻENIE, co oznacza, że błędy nie będą wyświetlane.
  Serial.begin(115200);
  // preferences.begin("wifi-config", false);
  wifiManager.setupWiFi();
  webServerHandler.setup();
  ntpClientHandler.setup();
}

void loop() {
  webServerHandler.update();
  // NTPClientHandler::update();
}
