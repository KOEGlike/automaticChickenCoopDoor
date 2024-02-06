#include "classes/chicken_door.hpp"
#include "classes/async_handler.hpp"
#include "classes/interfaces.hpp"

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
  GPIO_NUM_4,//dir pin
  GPIO_NUM_5,//step pin
  GPIO_NUM_18,//enable pin
  GPIO_NUM_17,//m0
  GPIO_NUM_16,//m1
  GPIO_NUM_15//m2
  };


WiFiConfig wifiConfig{
  strdup("nova sepsi"), //ssid
  strdup("MarciFanni"), //password
  strdup("0656d8aed024425599c985770726c7fb")//ipGeoLocationKey
  };

ChickenDoor door(&displayUiConfig, &motorConfig, &wifiConfig);

time_t syncFunc()
{
  return door.timesManager.getCurrentTime();
}

void setup() {
  Serial.begin(115200);
  Serial.println("Starting...");
  door.begin();
  setSyncProvider(syncFunc);
  setSyncInterval(60);
  ButtonManager.begin();
}

void loop() 
{
  Async.check();
}

/*DRV8825 motor{motorConfig.steps, motorConfig.dir, motorConfig.step, motorConfig.enable, motorConfig.m0, motorConfig.m1, motorConfig.m2};

void setup() {
  motor.begin(200);
  motor.setEnableActiveState(HIGH);
  motor.enable();
  motor.move(10000);
};

void loop() {}*/