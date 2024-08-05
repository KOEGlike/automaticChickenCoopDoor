#include "classes/chicken_door.hpp"
#include "classes/async_handler.hpp"
#include "classes/interfaces.hpp"

//Powered by SunriseSunset.io

DisplayUiConfig displayUiConfig{
  GPIO_NUM_0,//clk
  GPIO_NUM_10,//dio
  GPIO_NUM_1,//btn1 (left)
  GPIO_NUM_3,//bnt2 (right)
  GPIO_NUM_2//btn pwr
  };
MotorConfig motorConfig{
  200,//stepper motor steps amount
  GPIO_NUM_19,//dir pin
  GPIO_NUM_18,//step pin
  GPIO_NUM_9,//enable pin
  GPIO_NUM_8,//m0
  GPIO_NUM_7,//m1
  GPIO_NUM_6//m2
  };


WiFiConfig wifiConfig{
  strdup("Wokwi-GUEST"), //ssid
  strdup(""), //password
  strdup("0656d8aed024425599c985770726c7fb")//ipGeoLocationKey
  };

//ChickenDoor door(&displayUiConfig, &motorConfig, &wifiConfig);

// time_t syncFunc()
// {
//   return door.timesManager.getCurrentTime();
// }

CustomDisplayBehavior display(0, 10);

void setup() {
  Serial.begin(115200);
  Serial.println("Starting...");
  //door.begin();
  //setSyncProvider(syncFunc);
  //setSyncInterval(60);
  //ButtonManager.begin();
  display.begin();
  display.display.setBrightness(7);
  display.display.showNumberDecEx(1234);
  display.blinkSegments(0b0100, 3000, 3000, 5, []() {display.display.showNumberDecEx(4321);});
  display.blinkDotsPeriodically(0b01000000,5, 3000, 3000, 500,2, []() {Serial.println("done");});
}

void loop() 
{
  Async.check();
}