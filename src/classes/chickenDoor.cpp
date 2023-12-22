#include "ChickenDoor.hpp"
#include "memory_manager.hpp"

ChickenDoor::ChickenDoor(DisplayUiConfig *displayUiConfig, MotorConfig *motorConfig):
motor{motorConfig},
displayUI{&motor ,displayUiConfig}
{
}


void ChickenDoor::begin()
{
  displayUI.begin();
  motor.begin();
  
  TimesManager.updateTimeSate(MemoryManager.loadTimeStateFromMemory());
  if(TimesManager.getTimeState().sunsetMode)
    TimesManager.getTimeState().moveTimes=WiFiHandler.sunsetTimes();
}