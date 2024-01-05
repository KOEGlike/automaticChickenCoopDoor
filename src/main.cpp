#include "classes/chicken_door.hpp"
#include "classes/async_handler.hpp"
#include "classes/interfaces.hpp"
#include "classes/physical_interface/button.hpp"
#include "classes/WiFi_handler.hpp"
#include "classes/memory_manager.hpp"
#include <TimeAlarms.h>
#include "classes/times_manager.hpp"

//Powered by SunriseSunset.io

DisplayUiConfig displayUiConfig{
  GPIO_NUM_10,//clk
  GPIO_NUM_11,//dio
  GPIO_NUM_9,//btn1 (left)
  GPIO_NUM_11,//bnt2 (right)
  GPIO_NUM_10//btn pwr
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
  return door.timesManager.syncFunc();
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