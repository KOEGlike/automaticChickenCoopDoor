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
   Serial.println("registering callback");
  return maxCurrentId++;
}


void AsyncHandler::check()
{
   Serial.println("async check");
  if(callbacks.size()==0)
  {
    return;
  }
 
  if(callbacks.size()==0)
  {
    return;
  }
  
  for (const auto &ele :callbacks)
  {
    if(callbacks[ele.first].timesCalled>=callbacks[ele.first].times&&callbacks[ele.first].times>=0)
    {
      callbacks[ele.first].onend();
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