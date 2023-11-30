#ifndef WIFI_HANDLER_HPP
#define WIFI_HANDLER_HPP

#include "interfaces.hpp"
#include <TimeLib.h>
#include <WiFi.h>

class WiFiHandler_t
{
  public:
    WiFiHandler_t ();
    void begin(const char* ssid,const char* password,const char* ipGeoLoacationKey);
    MoveTimes sunsetTimes();
    tmElements_t gmtTime();
    tmElements_t ipTime();
  private:
    char* m_ssid, *m_password, *m_ipGeoLocationKey;

};

inline WiFiHandler_t WiFiHandler;

#endif