#include "async_handler.hpp"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <string>

struct callbackData
{
  callbackData(long delayInMillis,uint32_t timesToRepeat, std::function<void(void)> callBack, std::function<void(void)> onEnd, bool doDelayFirst=false, std::string name="");
  unsigned long delay=0;
  int32_t times=0, timesCalled=0;
  std::function<void(void)> callback=[](){}, onEnd=[](){};
  bool doDelayFirst=false;
  std::string name;
};

callbackData::callbackData(
  long delayInMillis,
  uint32_t timesToRepeat, 
  std::function<void(void)> callBack,
  std::function<void(void)> onEnd, 
  bool doDelayFirst, 
  std::string name
) {
    this->delay=delayInMillis;
    this->times=timesToRepeat;
    this->callback=callBack;
    this->onEnd=onEnd;
    this->doDelayFirst=doDelayFirst;
    Serial.println(name.c_str());
    this->name=name;
}

void AsyncHandler::deleteCallBack(TaskHandle_t id)
{
  vTaskDelete(id);
}

void callBackFunction(void* data)
{
  callbackData* callbackData = (struct callbackData*)data;
  const TickType_t ticks=pdMS_TO_TICKS(callbackData->delay);
  if(callbackData->doDelayFirst)
  {
    vTaskDelay(ticks);
  }
  while(callbackData->times<0 || (callbackData->timesCalled < callbackData->times))
  {
    callbackData->callback();
    callbackData->timesCalled++;
    if((callbackData->timesCalled<callbackData->times) || callbackData->times<0)
    {
      vTaskDelay(ticks);
    }
  }
  callbackData->onEnd();
  delete callbackData;
}

TaskHandle_t AsyncHandler::registerCallback(const char* name ,unsigned long delayInMillis,uint32_t times, std::function<void()> callback,std::function<void(void)> onEnd, bool doDelayFirst)
{
  TaskHandle_t taskHandle;
  xTaskCreate(
    callBackFunction,
    name,
    5000,
    new callbackData(delayInMillis,times,callback,onEnd,doDelayFirst, name),
    1,
    &taskHandle
  );
  return taskHandle;
}

void AsyncHandler::enableCallBack(TaskHandle_t  id)
{
  vTaskResume(id);
}

void AsyncHandler::disableCallBack(TaskHandle_t  id)
{
  vTaskSuspend(id);
}
