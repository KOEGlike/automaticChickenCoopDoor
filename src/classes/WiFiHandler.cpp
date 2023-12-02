#include "WiFiHandler.hpp"
#include <cstring>
#include <TimeAlarms.h>
#include <TimeLib.h>
#include <ArduinoJson.h>
#include <Arduino.h> 
#include <string>

void WiFiHandler_t::begin(char ssid[],char password[],char ipGeoLoacationKey[])
{
 m_ssid=ssid;
 m_password=password;
 m_ipGeoLocationKey=ipGeoLoacationKey;

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  WiFi.setAutoReconnect(true);

  while (WiFi.status() != WL_CONNECTED)
  {
   
  }
  setLocation();
  
}

MoveTimes WiFiHandler_t::sunsetTimes()
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
  MoveTimes times {convertShityStringTimeNotationFronSunsetApi(sunrise),convertShityStringTimeNotationFronSunsetApi(sunset)};
  return times;

}

tmElements_t WiFiHandler_t::convertShityStringTimeNotationFronSunsetApi(std::string shityFormat)
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

void WiFiHandler_t::setLocation()
{
  StaticJsonDocument<1536> json=ipGeolocReqest();
  m_lat=json["latitude"];
  m_lng=json["longitude"];
  Serial.println(m_lat);
  Serial.println(m_lng);
}

StaticJsonDocument<1536> WiFiHandler_t::ipGeolocReqest()
{
  HTTPClient http;
  StaticJsonDocument<1536> json;
  std::string path="https://api.ipgeolocation.io/ipgeo?apiKey="+std::string{m_ipGeoLocationKey};
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

tmElements_t WiFiHandler_t::ipTime()
{
  tmElements_t tm; tm.Hour=0; tm.Minute=0;
  StaticJsonDocument<1536> json=ipGeolocReqest();
  breakTime(json["time_zone"]["current_time_unix"], tm);
  tm.Hour=tm.Hour+json["time_zone"]["offset"].as<uint8_t>();
  Serial.println(tm.Hour);
  Serial.println(tm.Minute);
  return tm;
}

tmElements_t WiFiHandler_t::UTCTime()
{
  tmElements_t tm; tm.Hour=0; tm.Minute=0;
  StaticJsonDocument<1536> json=ipGeolocReqest();
  breakTime(json["time_zone"]["current_time_unix"], tm); 
  return tm;
}