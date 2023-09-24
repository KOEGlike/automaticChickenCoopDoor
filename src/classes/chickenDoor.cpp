#include "ChickenDoor.hpp"


ChickenDoor::ChickenDoor():
moveTimes{12,12,12,12},
displayUiConfig(21,22, 19,18),
interface{get, update, updateCurrentTime},
displayUI{interface,displayUiConfig}
{
  Serial.println("ChickenDoor constructor"); //delay(500);
}


