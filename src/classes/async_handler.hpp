#ifndef ASYNC_HANDLER
#define ASYNC_HANDLER

#include <functional>
#include <inttypes.h>
#include <Arduino.h>
#include<map>

struct callbackData
{
  callbackData() = default;
  callbackData(long delayInMillis,uint32_t timesToRepeat, std::function<void(void)> callBack, std::function<void(void)> onEnd);
  unsigned long delay=0, lastCalled=0;
  int32_t times=0, timesCalled=0;
  std::function<void(void)> callback=[](){}, onend=[](){};
};

class AsyncHandler{
  public:
    uint32_t registerCallback(unsigned long delay,uint32_t times, std::function<void(void)> callback,std::function<void(void)> onEnd=[](){},bool doDelayFirst=false);
    void deleteCallBack(uint32_t id);
    void check();
  private:
    std::map<uint32_t,callbackData> callbacks;
    uint32_t maxCurrentId=0;
};

inline AsyncHandler Async;

#endif
