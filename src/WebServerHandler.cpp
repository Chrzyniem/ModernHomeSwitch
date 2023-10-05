#include "WebServerHandler.h"
#include "WiFiManager.h"
#include "NTPClientHandler.h"
#include "DeviceInfoHandler.h"
#include <Preferences.h>
#include <DNSServer.h>
#include <WebServer.h>
extern void handleRoot();
extern void handleWiFi();
extern void handleSettings();
extern void handleConnect();
extern void handleInfo();
extern void handleConnectPost();
extern void handleReset();

Preferences preferences;
DNSServer dnsServer;
WebServer server(80);

String WiFiManager::clientSSID = "";
String WiFiManager::clientPassword = "";

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

// Dodatkowe funkcje obsługi serwera WWW, takie jak handleRoot, handleWiFi, handleSettings, handleInfo, handleConnect, handleConnectPost, handleReset.
void handleRoot() {
  server.send(200, "text/html", WebServerHandler::getHTML("Modern Home Web Server", ""));
}

void handleWiFi() {
  server.send(200, "text/html", WebServerHandler::getHTML("Available WiFi Networks", WiFiManager::getWiFiList()));
}

void handleSettings() {
  server.send(200, "text/html", WebServerHandler::getHTML("Settings", WiFiManager::getWiFiList()));
}

void handleInfo() {
  String html = DeviceInfoHandler::getDeviceInfo();
  // String html = "<h1>Device Info</h1>";
  
  // // Dodaj informacje o MAC adresie
  // String mac = WiFi.macAddress();
  // html += "<p>MAC Address: " + mac + "</p>";
  
  // // Dodaj informacje o napięciu zasilania
  // float voltage = analogRead(34) * (3.3 / 4095.0); // Przykładowy kod, dostosuj do swojego układu
  // html += "<p>Voltage: " + String(voltage) + " V</p>";
  
  // // Dodaj informacje o nazwie hosta
  // String hostname = WiFi.getHostname();
  // html += "<p>Hostname: " + hostname + "</p>";
  
  // // Dodaj informacje o czasie z serwera NTP
  // if (WiFi.status() == WL_CONNECTED) {
  //   html += "<p>Current Date: " + NTPClientHandler::getCurrentDate() + "</p>";
  //   html += "<p>Current Time: " + NTPClientHandler::getCurrentTime() + "</p>";
  // } else {
  //   html += "<p>Unable to get the time, device is not connected to the internet.</p>";
  // }

//  if (WiFi.status() == WL_CONNECTED) {
//    html += "<p>Current Time: " + NTPClientHandler::timeClient.getFormattedTime() + "</p>";
//  } else {
//    html += "<p>Unable to get the time, device is not connected to the internet.</p>";
//  }
  
  html += "<br><a href='#' onclick='if(confirm(\"Are you sure you want to reset to factory settings?\")) window.location=\"/reset\";'>Reset to Factory Settings</a>";
  html += "<br><a href='/'>Back</a>";
  server.send(200, "text/html", WebServerHandler::getHTML("Device Info", html));
}

void handleConnect() {
  String localSSID = server.arg("localSSID");
  
 

  String html = "<form method='POST' action='/connect'>";
  html += "<label for='localSSID'>SSID:</label>";
  html += "<input type='text' id='localSSID' name='localSSID' value='" + localSSID + "' readonly><br>";
  html += "<label for='inputPassword'>Password:</label>";
  html += "<input type='password' id='inputPassword' name='inputPassword' required><br>";
  html += "<input type='submit' value='Connect'>";
  html += "</form>";
  server.send(200, "text/html", WebServerHandler::getHTML("Connect to " + localSSID, html));
   // Przypisz wartość clientSSID do zmiennej statycznej WiFiManager::clientSSID
  WiFiManager::clientSSID = localSSID;
  Serial.println("Trying to connect with SSID: " + localSSID);
}

void handleConnectPost() {
    WiFiManager::clientSSID = server.arg("localSSID");
    WiFiManager::clientPassword = server.arg("inputPassword");
    preferences.begin("wifi-config", false);
    // Zapisz SSID i hasło klienta do preferencji
    preferences.putString("clientSSID", WiFiManager::clientSSID);
    preferences.putString("clientPassword", WiFiManager::clientPassword);

    Serial.println("Zapisalem SSID: " + WiFiManager::clientSSID + " and Password: " + WiFiManager::clientPassword);

    // Odłącz od obecnej sieci, jeśli jesteś podłączony
    WiFi.disconnect();

    // Próbuj połączyć się z nową siecią
    WiFi.begin(WiFiManager::clientSSID.c_str(), WiFiManager::clientPassword.c_str());
    unsigned long startTime = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - startTime < 20000) {
      delay(200);
    }

    // WiFi.begin(WiFiManager::clientSSID.c_str(), WiFiManager::clientPassword.c_str());
    // delay(3000); // Czekaj 3 sekund na połączenie

    if (WiFi.status() == WL_CONNECTED) {
        server.send(200, "text/html", "<p>Connected! ESP32 will restart now.</p>");
        delay(2000); // Czekaj 1 sekundę przed ponownym uruchomieniem
        ESP.restart();
    } else {
        server.send(200, "text/html", "<p>Connection failed! Please go back and try again.</p>");
    }
    preferences.end();
}


void handleReset() {
  preferences.begin("wifi-config", false);
  preferences.remove("clientSSID");
  preferences.remove("clientPassword");
  preferences.end();
  server.send(200, "text/html", "<p>Device has been reset to factory settings! It will now restart.</p>");
  delay(2000); // Wait 0,5 second before restarting
  ESP.restart();
}
