#ifndef WIFI_HANDLER_HPP
#define WIFI_HANDLER_HPP

#include "interfaces.hpp"
#include <TimeLib.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <string.h>

class WiFiHandler_t
{
  public:
    void begin(char ssid[],char password[],char ipGeoLoacationKey[]);
    MoveTimes sunsetTimes();
    tmElements_t UTCTime();
    tmElements_t ipTime();
  private:
    char* m_ssid, *m_password, *m_ipGeoLocationKey;
    float m_lat=0, m_lng=0;
    tmElements_t convertShityStringTimeNotationFronSunsetApi(std::string shityFormat);
    void setLocation();
    String ipGeolocReqest();
};

inline WiFiHandler_t WiFiHandler;

#endif