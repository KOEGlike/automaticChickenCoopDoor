#include "WiFi_handler.hpp"
#include <cstring>
#include <TimeAlarms.h>
#include <TimeLib.h>
#include <ArduinoJson.h>
#include <Arduino.h> 
#include <string>

WiFiHandler::WiFiHandler(WiFiConfig *wifiConfig)
{
  this->wifiConfig = wifiConfig;
}

void WiFiHandler::begin()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(wifiConfig->ssid, wifiConfig->password);
  WiFi.setAutoReconnect(true);

  while (WiFi.status() != WL_CONNECTED)
  {
   
  }
  setLocation();
  
}

MoveTimes WiFiHandler::sunsetTimes()
{
  HTTPClient http;
  std::string path ="https://api.sunrisesunset.io/json?lat="+std::to_string(m_lat)+"&lng="+std::to_string(m_lng);
  http.begin(path.c_str());
  int httpCode = http.GET();
  if(httpCode < 0)
  {
    Serial.println("Error on HTTP request");
    Serial.println(httpCode);
    return MoveTimes(0,0,0,0);
  }
  
  String payload = http.getString();
  http.end();
  StaticJsonDocument<512> json;
  DeserializationError error = deserializeJson(json, payload);
  if(error)
  {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    return MoveTimes(0,0,0,0);
  }
  
  std::string sunset = json["results"]["sunset"], sunrise=json["results"]["sunrise"];
  MoveTimes times {convertShityStringTimeNotationFromSunsetApi(sunrise),convertShityStringTimeNotationFromSunsetApi(sunset)};
  return times;

}

tmElements_t WiFiHandler::convertShityStringTimeNotationFromSunsetApi(std::string shityFormat)
{
  uint8_t hour=0,minute=0;
  while(shityFormat[0]!=':')
  {
    hour=hour*10+(shityFormat[0]-'0');
    shityFormat.erase(0,1);
  }
  shityFormat.erase(0,1);
  while (shityFormat[0]!=':')
  {
    minute=minute*10+(shityFormat[0]-'0');
    shityFormat.erase(0,1);
  }
  shityFormat.erase(0,4);
  if(shityFormat=="PM")hour+=12;
  tmElements_t tm;
  tm.Hour=hour;
  tm.Minute=minute;
  return tm;
}

void WiFiHandler::setLocation()
{
  StaticJsonDocument<1536> json=ipGeolocationRequest();
  m_lat=json["latitude"];
  m_lng=json["longitude"];
}

StaticJsonDocument<1536> WiFiHandler::ipGeolocationRequest()
{
  HTTPClient http;
  StaticJsonDocument<1536> json;
  std::string path="https://api.ipgeolocation.io/ipgeo?apiKey="+std::string{wifiConfig->ipGeolocationAPIkey};
  http.begin(path.c_str());
  int httpCode = http.GET();
  if(httpCode < 0)
  {
    Serial.println("Error on HTTP request");
    Serial.println(httpCode);
  return json;
  }
      
  String payload = http.getString();
  http.end();

  DeserializationError error = deserializeJson(json, payload);
  if(error)
  {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
  }

  return json;
}; 

tmElements_t WiFiHandler::ipTime()
{
  tmElements_t tm; tm.Hour=0; tm.Minute=0;
  StaticJsonDocument<1536> json=ipGeolocationRequest();
  breakTime(json["time_zone"]["current_time_unix"], tm);
  tm.Hour=tm.Hour+json["time_zone"]["offset"].as<uint8_t>();
  return tm;
}

tmElements_t WiFiHandler::UTCTime()
{
  tmElements_t tm; tm.Hour=0; tm.Minute=0;
  StaticJsonDocument<1536> json=ipGeolocationRequest();
  breakTime(json["time_zone"]["current_time_unix"], tm); 
  return tm;
}