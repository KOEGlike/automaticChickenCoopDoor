#ifndef ASYNC_HANDLER
#define ASYNC_HANDLER

#include <functional>
#include <inttypes.h>
#include<map>

struct callback_data
{
  callback_data(long delayInMillis,uint32_t timesToRepeat, std::function<void(void)> callBack){
    delay=delayInMillis;
    times=timesToRepeat;
    callback=callBack;
  }
  unsigned long delay, timeToTillNextCall=0;
  int32_t times, timesCalled=0;
  std::function<void(void)> callback;
};

class AsyncHandler{
  public:
    uint32_t registerCallback(unsigned long delay,uint32_t times, std::function<void(void)> callback);
    void deleteCallback(uint32_t id);
    void check();
  private:
    std::map<uint32_t,callback_data> calllbacks;
    uint32_t maxCurrentId=0;
};

#endif