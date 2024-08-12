#pragma once
#include <functional>
#include <inttypes.h>
#include <Arduino.h>
#include<map>



class AsyncHandler{
  public:
    TaskHandle_t registerCallback(std::string name, unsigned long delayInMillis,uint32_t times, std::function<void(void)> callback,std::function<void(void)> onEnd=[](){},bool doDelayFirst=false);
    void deleteCallBack(TaskHandle_t id);
    void enableCallBack(TaskHandle_t id);
    void disableCallBack(TaskHandle_t id);
};

inline AsyncHandler Async;


