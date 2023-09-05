#include "async_handler.hpp"

void AsyncHandler::deleteCallback(uint32_t id)
{
    calllbacks.erase(id);
}

uint32_t AsyncHandler::registerCallback(unsigned long delay,uint32_t times, std::function<void()> callback)
{
  calllbacks[maxCurrentId]=callback_data{delay,times,callback};
  return maxCurrentId++;
}


void AsyncHandler::check()
{
  std::map<uint32_t,callback_data>::iterator it =calllbacks.begin();
  while (it != calllbacks.end())
  {
    if(it->second.timeToTillNextCall<=0)
    {
      it->second.callback();
      it->second.timeToTillNextCall=it->second.delay;
      it->second.timesCalled++;
    }
    if(it->second.times>0)
    {
      it->second.timesCalled++;
    }
    if(it->second.timesCalled>=it->second.times)
    {
      deleteCallback(it->first);
    }
    ++it;
  }
}