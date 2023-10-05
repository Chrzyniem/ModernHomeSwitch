#pragma once
#include <WebServer.h>
#include <Preferences.h>

extern Preferences preferences;

class WebServerHandler {
public:
  static void setup();
  static void update();
  static String getHTML(String title, String content);
};
