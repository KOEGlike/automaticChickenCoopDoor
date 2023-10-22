#include "async_handler.hpp"



void AsyncHandler::deleteCallBack(uint32_t id)
{
    callbacks.erase(id);
}

callbackData::callbackData(long delayInMillis,uint32_t timesToRepeat, std::function<void(void)> callBack,std::function<void(void)> onEnd){
    delay=delayInMillis;
    times=timesToRepeat;
    callback=callBack;
    onend=onEnd;
    
  }

uint32_t AsyncHandler::registerCallback(unsigned long delay,uint32_t times, std::function<void()> callback,std::function<void(void)> onEnd, bool doDelayFirst)
{
  callbackData cbd(delay,times,callback,onEnd);
  if(doDelayFirst)
  {
    cbd.lastCalled=millis();
  }
  callbacks[maxCurrentId]=cbd;
  return maxCurrentId++;
}


void AsyncHandler::check()
{
  if(callbacks.size()==0)
  {
    return;
  }
 
  if(callbacks.size()==0)
  {
    return;
  }
  
  for (const auto &[id, callback] :callbacks)
  {
    if(callbacks[id].timesCalled>=callbacks[id].times&&callbacks[id].times>=0)
    {
      callbacks[id].onend();
      deleteCallBack(id);
    }
    else if(millis()-callbacks[id].lastCalled>=callbacks[id].delay)
    {
      callbacks[id].callback();
      
      callbacks[id].lastCalled=millis();
      if(callbacks[id].times>0)
      {
        callbacks[id].timesCalled++;
      }    
    }
  }
}