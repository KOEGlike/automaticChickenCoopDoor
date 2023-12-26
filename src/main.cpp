#include "classes/chickenDoor.hpp"
#include "classes/async_handler.hpp"
#include "classes/interfaces.hpp"
#include "classes/physical_interface/button.hpp"
#include "classes/WiFiHandler.hpp"
#include "classes/memory_manager.hpp"
#include <TimeAlarms.h>
#include "classes/times_manager.hpp"

//Powered by SunriseSunset.io

DisplayUiConfig displayUiConfig{
  10,//clk
  11,//dio
  9,//btn1 (left)
  11,//bnt2 (right)
  10//btn pwr
  };
MotorConfig motorConfig{
  200,//stepper motor steps amount
  4,//dir pin
  5,//step pin
  7,//enable pin
  17,//m0
  16,//m1
  15//m2
  };


WiFiConfig wifiConfig{
  strdup("nova sepsi"), //ssid
  strdup("MarciFanni"), //password
  strdup("0656d8aed024425599c985770726c7fb")//ipGeoLocationKey
  };

ChickenDoor door(&displayUiConfig, &motorConfig, &wifiConfig);

time_t syncFunc()
{
  return door.TimesManager.syncFunc();
}

void setup() {
  Serial.begin(115200);
  door.begin();
  setSyncProvider(syncFunc);
  setSyncInterval(30);
  ButtonManager.begin();
}

void loop() 
{
  Async.check();
}


/*

#include <TimeLib.h>
#include <TimeAlarms.h>
#include <Arduino.h>

void alarm_callback()
{
  Serial.println("did something");
}

void setup()
{
    Serial.begin(115200);
    Alarm.delay(100);
    tmElements_t tm;
    setTime(13, 5, 0, 25, 12, 2023);
    //breakTime(now(), tm);
    tm.Day=1;
    
    tm.Hour=7;
    tm.Minute=34;
    int alarmID=Alarm.alarmRepeat(0, alarm_callback);
    Alarm.write(alarmID,makeTime(tm));
    breakTime(Alarm.read(alarmID),tm);
    Serial.println(tm.Hour);
    Serial.println(tm.Minute);
}

void loop()
{

}*/
