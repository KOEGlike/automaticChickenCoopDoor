#include "ChickenDoor.hpp"


ChickenDoor::ChickenDoor():
moveTimes{12,12,12,12},
displayUiConfig(4,5,6,7),
interface{get, update, updateCurrentTime, getCurrentTime},
displayUI{interface,displayUiConfig}
{
  Serial.println("ChickenDoor constructor"); 
}


