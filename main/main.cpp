#include "classes/chicken_door.hpp"
#include "classes/async_handler.hpp"
#include "classes/interfaces.hpp"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "nvs.h"

//Powered by SunriseSunset.io

std::shared_ptr<DisplayUiConfig> displayUiConfig=std::make_shared<DisplayUiConfig> (
  GPIO_NUM_0,//clk
  GPIO_NUM_10,//dio
  GPIO_NUM_1,//btn1 (left)
  GPIO_NUM_3,//bnt2 (right)
  GPIO_NUM_2//btn pwr
);

std::shared_ptr<MotorConfig> motorConfig=std::make_shared<MotorConfig> (
  200,//stepper motor steps amount
  GPIO_NUM_19,//dir pin
  GPIO_NUM_18,//step pin
  GPIO_NUM_9,//enable pin
  GPIO_NUM_8,//m0
  GPIO_NUM_7,//m1
  GPIO_NUM_6//m2
);


std::shared_ptr<WiFiConfig> wifiConfig=std::make_shared<WiFiConfig> (
  strdup("Wokwi-GUEST"), //ssid
  strdup(""), //password
  strdup("0656d8aed024425599c985770726c7fb")//ipGeoLocationKey
);

ChickenDoor door(displayUiConfig, motorConfig, wifiConfig);

time_t syncFunc()
{
  return door.timesManager->getCurrentTime();
}

extern "C" void app_main() {
  Serial.begin(115200); 
  esp_log_level_set("*", ESP_LOG_NONE);
  esp_err_t err= nvs_flash_init();
  switch (err) {
    case ESP_OK:
        printf("SP_OK: Storage was successfully initialized.\n");
        break;
    case ESP_ERR_NVS_NO_FREE_PAGES:
        printf("ESP_ERR_NVS_NO_FREE_PAGES: The NVS storage contains no empty pages.\n");
        break;
    case ESP_ERR_NOT_FOUND:
        printf("ESP_ERR_NOT_FOUND: No partition with label 'nvs' is found in the partition table.\n");
        break;
    case ESP_ERR_NO_MEM:
        printf("ESP_ERR_NO_MEM: Memory could not be allocated for the internal structures.\n");
        break;
    // Add cases for other specific error codes from the underlying flash storage driver
    // and from nvs_flash_read_security_cfg, nvs_flash_generate_keys, nvs_flash_secure_init_partition APIs
    default:
        printf("Unknown error: %d\n", err);
        break;
}

  Serial.println("Starting...");
  door.begin();
  
  
  // sets the sync provider function, what time is it right now
  setSyncProvider(syncFunc);
  // the interval in seconds between each sync
  setSyncInterval(60);
  ButtonManager.begin();
}