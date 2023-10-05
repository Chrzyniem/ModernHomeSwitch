// #pragma once
// #include <NTPClient.h>
// #include <WiFiUdp.h>


// class NTPClientHandler {
// public:
//   static void setup();
//   static void update();
//   static String getCurrentTime();
//   static NTPClient timeClient;
// };

#pragma once
#include <Timezone.h>

class NTPClientHandler {
public:
  static void setup();
  // static void update();
  static String getCurrentTime();
  static String getCurrentDate();
};