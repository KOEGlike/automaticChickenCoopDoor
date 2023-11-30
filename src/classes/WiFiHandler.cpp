#include "WiFiHandler.hpp"

void WiFiHandler_t::begin(const char* ssid,const char* password,const char* ipGeoLoacationKey)
{
  m_ssid = ssid;
  m_password = password;
  m_ipGeoLocationKey = ipGeoLoacationKey;
}