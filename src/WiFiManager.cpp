#include "WiFiManager.h"
#include <Preferences.h>

extern Preferences preferences;

// String WiFiManager::clientSSID = "";
// String WiFiManager::clientPassword = "";

void WiFiManager::setupWiFi() {
  preferences.begin("wifi-config", true);
  WiFiManager::clientSSID = preferences.getString("clientSSID", "");
  WiFiManager::clientPassword = preferences.getString("clientPassword", "");

  String mac = WiFi.macAddress();
  String suffix = mac.substring(mac.length() - 5);
  suffix.replace(":", "");
  String hostname = "ModernHome-" + suffix;
  WiFi.setHostname(hostname.c_str());

  String apSSID = hostname; // Ustaw domyślne SSID dla AP
  String apPassword = "modernhome"; // Ustaw domyślne hasło dla AP

  Serial.println("Trying to connect with SSID: " + WiFiManager::clientSSID + " and Password: " + WiFiManager::clientPassword);

  if (WiFiManager::clientSSID.length() == 0) {
    IPAddress apIP(192, 168, 10, 1);
    IPAddress gateway(192, 168, 10, 1);
    IPAddress subnet(255, 255, 255, 0);
    WiFi.softAPConfig(apIP, gateway, subnet);
    WiFi.softAP(apSSID.c_str(), apPassword.c_str());
  } else {
    WiFi.begin(WiFiManager::clientSSID.c_str(), WiFiManager::clientPassword.c_str());
    unsigned long startTime = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - startTime < 20000) {
      delay(200);
    }
    if (WiFi.status() != WL_CONNECTED) {

      IPAddress apIP(192, 168, 10, 1);
      IPAddress gateway(192, 168, 10, 1);
      IPAddress subnet(255, 255, 255, 0);
      WiFi.softAPConfig(apIP, gateway, subnet);
      WiFi.softAP(apSSID.c_str(), apPassword.c_str());
    }
  }

  if (WiFi.status() == WL_CONNECTED) {
      Serial.println("Connected to WiFi successfully!");
  } else {
      Serial.println("Failed to connect to WiFi. Starting in AP mode.");
  }

    // Zamknij przestrzeń nazw
  preferences.end();
}


String WiFiManager::getWiFiList() {
  String html = "<ul style='text-align: left;'>";
  int n = WiFi.scanNetworks();
  for (int i = 0; i < n; ++i) {
    html += "<li><a href='/connect?localSSID=" + WiFi.SSID(i) + "'>" + WiFi.SSID(i) + " (" + WiFi.RSSI(i) + " dBm)</a></li>";
  }
  html += "</ul>";
  return html;
}
