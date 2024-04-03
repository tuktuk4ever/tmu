constexpr const char * const TAG = "main";


// FreeRTOS includes
#include <freertos/FreeRTOS.h>

// esp-idf includes
#include <esp_log.h>
#if defined(CONFIG_ESP_TASK_WDT_PANIC) || defined(CONFIG_ESP_TASK_WDT)
#include <esp_task_wdt.h>
#endif

// local includes
#include "display_vesc.h"
#include "utils/tasks.h"

using namespace std::chrono_literals;

extern "C" [[noreturn]] void app_main()
{
    ESP_LOGI(TAG, "app_main() called");

#if defined(CONFIG_ESP_TASK_WDT_PANIC) || defined(CONFIG_ESP_TASK_WDT)
    {
        const auto taskHandle = xTaskGetCurrentTaskHandle();
        if (!taskHandle)
        {
            ESP_LOGE(TAG, "could not get handle to current main task!");
        }
        else if (const auto result = esp_task_wdt_add(taskHandle); result != ESP_OK)
        {
            ESP_LOGE(TAG, "could not add main task to watchdog: %s", esp_err_to_name(result));
        }
    }
#endif

    /*--- Task Manager ---*/
    for (const auto& task : tasks)
        task.setup();

#if defined(CONFIG_ESP_TASK_WDT_PANIC) || defined(CONFIG_ESP_TASK_WDT)
    if (const auto result = esp_task_wdt_reset(); result != ESP_OK)
        ESP_LOGE(TAG, "esp_task_wdt_reset() failed with %s", esp_err_to_name(result));
#endif

    espvesc::display_init();

    espchrono::millis_clock::time_point lastTaskPush = espchrono::millis_clock::now();

    while (true)
    {
        for (auto& task : tasks)
        {
            task.loop();

#if defined(CONFIG_ESP_TASK_WDT_PANIC) || defined(CONFIG_ESP_TASK_WDT)
            if (const auto result = esp_task_wdt_reset(); result != ESP_OK)
                ESP_LOGE(TAG, "esp_task_wdt_reset() failed with %s", esp_err_to_name(result));
#endif
        }

        if (espchrono::ago(lastTaskPush) > 1s)
        {
            lastTaskPush = espchrono::millis_clock::now();
            sched_pushStats(false);
        }

        vTaskDelay(1);
    }
}

