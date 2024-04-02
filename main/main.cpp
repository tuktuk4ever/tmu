constexpr const char * const TAG = "main";

// FreeRTOS includes
#include <freertos/FreeRTOS.h>

// esp-idf includes
#include <esp_log.h>

extern "C" [[noreturn]] void app_main()
{
  ESP_LOGI(TAG, "app_main() called");

  while (true)
  {
      vTaskDelay(1);
  }
}

