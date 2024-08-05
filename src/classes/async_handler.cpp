#include "async_handler.hpp"

void AsyncHandler::deleteCallBack(uint32_t id)
{
  callbacks.erase(id);
}

callbackData::callbackData(long delayInMillis,uint32_t timesToRepeat, std::function<void(void)> callBack,std::function<void(void)> onEnd){
    delay=delayInMillis;
    times=timesToRepeat;
    callback=callBack;
    this->onEnd=onEnd;
    
  }

uint32_t AsyncHandler::registerCallback(unsigned long delayInMillis,uint32_t times, std::function<void()> callback,std::function<void(void)> onEnd, bool doDelayFirst)
{
  callbackData cbd(delayInMillis,times,callback,onEnd);
  if(doDelayFirst)
  {
    cbd.lastCalled=millis();
  }
  callbacks[maxCurrentId]=cbd;
  return maxCurrentId++;
}

void AsyncHandler::enableCallBack(uint32_t id)
{
  callbacks[id].enabled=true;
}

void AsyncHandler::disableCallBack(uint32_t id)
{
  callbacks[id].enabled=false;
}


void AsyncHandler::check()
{
  if(callbacks.size()==0)
  {
    return;
  }
  
  for (const auto &[id, callback] :callbacks)
  {
    if(callbacks[id].timesCalled>=callbacks[id].times&&callbacks[id].times>=0)
    {
      callbacks[id].onEnd();
      deleteCallBack(id);
    }
    else if(callbacks[id].enabled && (callbacks[id].lastCalled==0 || millis()-callbacks[id].lastCalled>=callbacks[id].delay))
    {
      callbacks[id].lastCalled=millis();
      callbacks[id].callback();
      if(callbacks[id].times>0)
      {
        callbacks[id].timesCalled++;
      }    
    }
  }
}