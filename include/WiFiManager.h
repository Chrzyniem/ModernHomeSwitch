#pragma once
#include <WiFi.h>

class WiFiManager {
public:
  static void setupWiFi();
  static String getWiFiList();
};
