#include "WiFiManager.h"

void WiFiManager::setupWiFi() {
  String ssid = preferences.getString("ssid", "");
  String password = preferences.getString("password", "");
  
  String mac = WiFi.macAddress();
  String suffix = mac.substring(mac.length() - 5);
  suffix.replace(":", "");
  String hostname = "ModernHome-" + suffix;

  if (ssid.length() == 0) {
    IPAddress apIP(192, 168, 10, 1);
    IPAddress gateway(192, 168, 10, 1);
    IPAddress subnet(255, 255, 255, 0);
    WiFi.softAPConfig(apIP, gateway, subnet);
    WiFi.softAP(hostname.c_str(), password.c_str());
  } else {
    WiFi.begin(ssid.c_str(), password.c_str());
    unsigned long startTime = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - startTime < 20000) {
      delay(100);
    }
    if (WiFi.status() != WL_CONNECTED) {
      IPAddress apIP(192, 168, 10, 10);
      IPAddress gateway(192, 168, 10, 1);
      IPAddress subnet(255, 255, 255, 0);
      WiFi.softAPConfig(apIP, gateway, subnet);
      WiFi.softAP(hostname.c_str(), password.c_str());
    }
  }
}

String WiFiManager::getWiFiList() {
  String html = "<ul style='text-align: left;'>";
  int n = WiFi.scanNetworks();
  for (int i = 0; i < n; ++i) {
    html += "<li><a href='/connect?ssid=" + WiFi.SSID(i) + "'>" + WiFi.SSID(i) + " (" + WiFi.RSSI(i) + " dBm)</a></li>";
  }
  html += "</ul>";
  return html;
}
