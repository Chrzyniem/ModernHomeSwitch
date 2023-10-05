#include "NTPClientHandler.h"
#include <WiFi.h>
#include <Timezone.h>
#include "WiFiManager.h"

// Czas letni dla Europy/Warszawy (ostatnia niedziela marca do ostatniej niedzieli października)
TimeChangeRule CEST = {"CEST", Last, Sun, Mar, 2, 120}; // UTC + 2 godziny
// Czas standardowy dla Europy/Warszawy
TimeChangeRule CET = {"CET", Last, Sun, Oct, 3, 60};   // UTC + 1 godzina
Timezone myTZ(CEST, CET);

// WiFiUDP ntpUDP;
// NTPClient NTPClientHandler::timeClient(ntpUDP, "pool.ntp.org", 0, 120000);

void NTPClientHandler::setup() {
  if (WiFi.status() == WL_CONNECTED) {
    configTime(0, 0, "pool.ntp.org", "time.nist.gov");
  }
}

// String NTPClientHandler::getCurrentTime() {
//   return timeClient.getFormattedTime();
// }

String NTPClientHandler::getCurrentTime() {
    time_t now = time(nullptr); // Pobierz aktualny czas
    time_t localTime = myTZ.toLocal(now); // Konwersja na czas lokalny
    
    char formattedTime[9]; // Przygotuj bufor na sformatowany czas
    sprintf(formattedTime, "%02d:%02d:%02d", hour(localTime), minute(localTime), second(localTime));
    
    return String(formattedTime);
}

// String NTPClientHandler::getCurrentTime() {
//     time_t utc = now(); // Pobierz aktualny czas
//     time_t localTime = myTZ.toLocal(utc); // Konwersja na czas lokalny
    
//     char formattedTime[9]; // Przygotuj bufor na sformatowany czas
//     sprintf(formattedTime, "%02d:%02d:%02d", hour(localTime), minute(localTime), second(localTime));
    
//     return String(formattedTime);
// }
String NTPClientHandler::getCurrentDate() {
    time_t now = time(nullptr); // Pobierz aktualny czas
    time_t localTime = myTZ.toLocal(now); // Konwersja na czas lokalny
    
    char formattedDate[11]; // Przygotuj bufor na sformatowaną datę
    sprintf(formattedDate, "%02d.%02d.%04d", 
            day(localTime), month(localTime), year(localTime));
    
    return String(formattedDate);
}