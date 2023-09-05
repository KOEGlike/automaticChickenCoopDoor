#ifndef ASYNC_HANDLER
#define ASYNC_HANDLER

#include <functional>
#include <inttypes.h>
#include<map>

class AsyncHandler{
  public:
    void registerCallback(uint32_t id, uint8_t type, std::function<void(void)> callback);
    void deleteCallback(uint32_t id);
    void check();
  private:
    std::map<uint32_t,std::pair<uint8_t, std::function<void(void)>>> calllbacks;
};

#endif