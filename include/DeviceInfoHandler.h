#pragma once
#include <WiFi.h>

class DeviceInfoHandler {
public:
  static String getDeviceInfo();
  static String startTime;
  static bool isStartTimeSet;
};
