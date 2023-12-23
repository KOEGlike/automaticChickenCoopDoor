#pragma once

#include "interfaces.hpp"
#include <TimeLib.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <string.h>
#include <ArduinoJson.h>

class MoveTimes;

class WiFiHandler_t
{
  public:
    WiFiHandler_t(WiFiConfig *wifiConfig);
    void begin();
    MoveTimes sunsetTimes();
    tmElements_t UTCTime();
    tmElements_t ipTime();
  private:
    float m_lat=0, m_lng=0;
    tmElements_t convertShityStringTimeNotationFromSunsetApi(std::string shityFormat);
    void setLocation();
    StaticJsonDocument<1536> ipGeolocationRequest();
    WiFiConfig *wifiConfig;
};
