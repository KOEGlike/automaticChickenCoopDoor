#include "async_handler.hpp"

void AsyncHandler::deleteCallBack(uint32_t id)
{
    callbacks.erase(id);
}

callbackData::callbackData(long delayInMillis,uint32_t timesToRepeat, std::function<void(void)> callBack){
    delay=delayInMillis;
    times=timesToRepeat;
    callback=callBack;
  }

uint32_t AsyncHandler::registerCallback(unsigned long delay,uint32_t times, std::function<void()> callback, bool doDelayFirst)
{
  callbackData cbd(delay,times,callback);
  if(doDelayFirst)
  {
    cbd.lastCalled=millis();
  }
  callbacks[maxCurrentId]=cbd;
  return maxCurrentId++;
}


void AsyncHandler::check()
{
  for (const auto &ele :callbacks)
  {
    if(callbacks[ele.first].timesCalled>=callbacks[ele.first].times)
    {
      deleteCallBack(ele.first);
    }
    else if(millis()-callbacks[ele.first].lastCalled>=callbacks[ele.first].delay)
    {
      callbacks[ele.first].callback();
      callbacks[ele.first].lastCalled=millis();
      if(callbacks[ele.first].times>0)
      {
        callbacks[ele.first].timesCalled++;
      }    
    }
  }
}