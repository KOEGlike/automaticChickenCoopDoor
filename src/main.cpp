#include "classes/chickenDoor.hpp"
#include "classes/async_handler.hpp"
#include "classes/interfaces.hpp"
#include "classes/physical_interface/button.hpp"
#include "classes/WiFiHandler.hpp"

//Powered by SunriseSunset.io

DisplayUiConfig displayUiConfig{
  10,//clk
  11,//dio
  8,//btn1 (left)
  9,//bnt2 (right)
  3//btn pwr
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

char ssid[] = "nova sepsi";
char password[] = "MarciFanni";
char ipGeoLocationKey[] = "0656d8aed024425599c985770726c7fb";

ChickenDoor door(&displayUiConfig, &motorConfig);

time_t syncFunc()
{
  return door.syncFunc();
}

void setup() {
  Serial.begin(115200);
  WiFiHandler.begin(ssid, password, ipGeoLocationKey);
  ButtonManager.begin();
  door.begin();
 setSyncProvider(syncFunc);
}

void loop() 
{
  Async.check();
}
