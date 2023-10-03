#pragma once
#include <WebServer.h>

class WebServerHandler {
public:
  static void setup();
  static void update();
  static String getHTML(String title, String content);
};
