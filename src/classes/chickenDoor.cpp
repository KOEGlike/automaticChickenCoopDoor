#include "ChickenDoor.hpp"


ChickenDoor::ChickenDoor(DisplayUiConfig displayUiConfig):
moveTimes{12,12,12,12},
interface{get, update, updateCurrentTime, getCurrentTime,openDoor,closeDoor, getDoorState},
displayUI{interface,displayUiConfig}
{
  Serial.println("ChickenDoor constructor"); 
}


void ChickenDoor::begin()
{
  displayUI.begin();
}
