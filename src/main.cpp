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

char ssid[] = "nova sepsi";
char password[] = "MarciFanni";
char ipGeoLocationKey[] = "0656d8aed024425599c985770726c7fb";

ChickenDoor door(&displayUiConfig, &motorConfig);

time_t syncFunc()
{
  return TimesManager.syncFunc();
}

void TimesManagerSetup()
{
  const int idOpen=Alarm.alarmRepeat(0,[&]() {door.motor.changeState(1);});
  const int idClose=Alarm.alarmRepeat(0,[&]() {door.motor.changeState(0); Serial.println("close"); if(TimesManager.getTimeState().sunsetMode) TimesManager.updateMoveTimes(WiFiHandler.sunsetTimes());});
  TimesManager.begin(idClose, idClose);
}

void setup() {
  Serial.begin(115200);
  MemoryManager.begin();
  WiFiHandler.begin(ssid, password, ipGeoLocationKey);
   setSyncProvider(syncFunc);
  setSyncInterval(30);
  TimesManagerSetup();
  ButtonManager.begin();
  door.begin();
 
}

void loop() 
{
  Async.check();
}
