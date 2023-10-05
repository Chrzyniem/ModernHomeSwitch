#include "DeviceInfoHandler.h"
#include "NTPClientHandler.h"

String DeviceInfoHandler::startTime = "";
bool DeviceInfoHandler::isStartTimeSet = false;

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
    html += "<p>Current Date: " + NTPClientHandler::getCurrentDate() + "</p>";
    html += "<p>Current Time: " + NTPClientHandler::getCurrentTime() + "</p>";
  } else {
    html += "<p>Unable to get the time, device is not connected to the internet.</p>";
  }
  // Wyświetl czas startu
  
    if (!isStartTimeSet && NTPClientHandler::getCurrentDate() != "01.01.1970") {
      startTime = NTPClientHandler::getCurrentDate() + " " + NTPClientHandler::getCurrentTime();
      isStartTimeSet = true;
    }
    html += "<p>Start Date and Time: " + startTime + "</p>";

    // Wyświetl czas pracy
    unsigned long uptime = millis() / 1000;
    int days = uptime / 86400;
    uptime %= 86400;
    int hours = uptime / 3600;
    uptime %= 3600;
    int minutes = uptime / 60;
    html += "<p>Uptime: " + String(days) + " days, " + String(hours) + " hours, " + String(minutes) + " minutes</p>";

  return html;
}
