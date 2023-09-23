#include "ChickenDoor.hpp"


ChickenDoor::ChickenDoor(int lol, int xd):interface(get, update, updateCurrentTime),
displayUiConfig(21,22, 19,18 ), 
displayUI(interface,displayUiConfig)
{
  Serial.println("ChickenDoor constructor"); delay(500);

}


