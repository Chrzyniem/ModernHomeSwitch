#include "NTPClientHandler.h"
#include <WiFi.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "tempus1.gum.gov.pl", 3600, 60000);

void NTPClientHandler::setup() {
  if (WiFi.status() == WL_CONNECTED) {
    timeClient.begin();
  }
}

void NTPClientHandler::update() {
  if (WiFi.status() == WL_CONNECTED) {
    timeClient.update();
  }
}

String NTPClientHandler::getCurrentTime() {
  return timeClient.getFormattedTime();
}
