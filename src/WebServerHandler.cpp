#include "WebServerHandler.h"
#include "WiFiManager.h"
#include "NTPClientHandler.h"
#include "DeviceInfoHandler.h"
#include <Preferences.h>
#include <DNSServer.h>
#include <WebServer.h>

Preferences preferences;
DNSServer dnsServer;
WebServer server(80);

String WebServerHandler::getHTML(String title, String content) {
  String html = "<!DOCTYPE html>";
  html += "<html lang='en'>";
  html += "<head>";
  html += "<meta charset='UTF-8'>";
  html += "<title>" + title + "</title>";
  html += "<style>";
  html += "body { background-color: #121212; color: #ffffff; font-family: 'Arial', sans-serif; text-align: center; margin: 0; padding: 0; }";
  html += "nav { display: inline-block; margin-top: 50px; }";
  html += "a { background-color: #333333; color: #ffffff; display: inline-block; padding: 15px 25px; margin: 10px; border-radius: 15px; text-decoration: none; }";
  html += "a:hover { background-color: #555555; }";
  html += "</style>";
  html += "</head>";
  html += "<body>";
  html += "<h1>" + title + "</h1>";
  html += "<nav>";
  html += "<a href='/wifi'>WiFi</a>";
  html += "<a href='/settings'>Settings</a>";
  html += "<a href='/info'>Info</a>";
  html += "</nav>";
  html += "<div>" + content + "</div>";
  html += "</body>";
  html += "</html>";
  return html;
}

void WebServerHandler::setup() {
  server.on("/", handleRoot);
  server.on("/wifi", handleWiFi);
  server.on("/settings", handleSettings);
  server.on("/info", handleInfo);
  server.on("/connect", HTTP_GET, handleConnect);
  server.on("/connect", HTTP_POST, handleConnectPost);
  server.on("/reset", handleReset);
  server.onNotFound([]() {
    server.sendHeader("Location", String("http://") + WiFi.softAPIP().toString(), true);
    server.send(302, "text/plain", "");
  });

  server.begin();
}

void WebServerHandler::update() {
  dnsServer.processNextRequest();
  server.handleClient();
}

// ... (Tutaj umieść resztę kodu związanej z obsługą serwera WWW, taką jak metody handleRoot, handleWiFi, handleSettings, handleInfo, handleConnect, handleConnectPost, handleReset oraz odpowiednie zmienne i obiekty jak Preferences, DNSServer, WebServer.)
