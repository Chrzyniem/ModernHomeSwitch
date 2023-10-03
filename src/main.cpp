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
  Serial.begin(115200);
  wifiManager.setupWiFi();
  webServerHandler.setup();
  ntpClientHandler.setup();
}

void loop() {
  webServerHandler.update();
  ntpClientHandler.update();
}
