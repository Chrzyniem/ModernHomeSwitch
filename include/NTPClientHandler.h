#pragma once
#include <NTPClient.h>
#include <WiFiUdp.h>

class NTPClientHandler {
public:
  static void setup();
  static void update();
  static String getCurrentTime();
};
