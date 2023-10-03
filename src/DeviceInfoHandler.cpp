#include "DeviceInfoHandler.h"

String DeviceInfoHandler::getDeviceInfo() {
  String html = "<h1>Device Info</h1>";
  
  // Dodaj informacje o MAC adresie
  String mac = WiFi.macAddress();
  html += "<p>MAC Address: " + mac + "</p>";
  
  // Dodaj informacje o napięciu zasilania
  float voltage = analogRead(34) * (3.3 / 4095.0); // Przykładowy kod, dostosuj do swojego układu
  html += "<p>Voltage: " + String(voltage) + " V</p>";
  
  // Dodaj informacje o nazwie hosta
  String hostname = WiFi.getHostname();
  html += "<p>Hostname: " + hostname + "</p>";
  
  // Dodaj informacje o czasie z serwera NTP
  if (WiFi.status() == WL_CONNECTED) {
    html += "<p>Current Time: " + timeClient.getFormattedTime() + "</p>";
  } else {
    html += "<p>Unable to get the time, device is not connected to the internet.</p>";
  }
  
  return html;
}
