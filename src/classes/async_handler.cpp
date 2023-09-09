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

uint32_t AsyncHandler::registerCallback(unsigned long delay,uint32_t times, std::function<void()> callback)
{
  callbackData cbd(delay,times,callback);
  callbacks[maxCurrentId]=cbd;
  return maxCurrentId++;
}


void AsyncHandler::check()
{
  callbacks[maxCurrentId-1].callback();
  if(callbacks.size()==0)
  {
    return;
  }
  
  for (const auto &ele :callbacks)
  {
   Serial.println(callbacks.size());
   // Serial.println("xd");
    if(ele.second.timesCalled>=ele.second.times)
    {Serial.println("haha");
      deleteCallBack(ele.first);
    }
    if(millis()-ele.second.lastCalled>=ele.second.delay)
    {Serial.println("lololol");
      ele.second.callback();
      callbacks[ele.first].lastCalled=millis();
      if(ele.second.times>0)
      {
        callbacks[ele.first].timesCalled++;
      }    
    }
    
  }
}