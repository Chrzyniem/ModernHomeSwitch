#pragma once
#include <WiFi.h>

class WiFiManager {
public:
  static void setupWiFi();
  static String getWiFiList();
  static String clientSSID;
  static String clientPassword;
  static String apSSID;
  static String apPassword;
};
