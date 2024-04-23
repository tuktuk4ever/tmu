constexpr const char * const TAG = "main";


// FreeRTOS includes
#include <freertos/FreeRTOS.h>

// esp-idf includes
#include <esp_log.h>
#if defined(CONFIG_ESP_TASK_WDT_PANIC) || defined(CONFIG_ESP_TASK_WDT)
#include <esp_task_wdt.h>
#endif

// 3rdparty lib includes
#include <screenmanager.h>

// local includes
#include "control/buttons.h"
#include "display_vesc.h"
#include "utils/settings.h"
#include "utils/tasks.h"

// screens
#include "screens/buttonmapscreen.h"
#include "screens/mainscreen.h"

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
    /*--- Config ---*/
    if (const auto result = configs.init("tuktuk"); result != ESP_OK)
    {
        ESP_LOGE(TAG, "config_init_settings() failed with %s", esp_err_to_name(result));

        while (true)
        {
#if defined(CONFIG_ESP_TASK_WDT_PANIC) || defined(CONFIG_ESP_TASK_WDT)
            if (const auto res = esp_task_wdt_reset(); res != ESP_OK)
                ESP_LOGE(TAG, "esp_task_wdt_reset() failed with %s", esp_err_to_name(res));
#endif
            vTaskDelay(1);
        }
    }

    /*--- Display ---*/
    espvesc::display::init();

    espvesc::display::set_boot_msg("Starting...");

    if (!buttonsConfigured())
    {
        ESP_LOGW(TAG, "buttons not configured, starting button map screen");

        espgui::switchScreen<espvesc::ButtonMapScreen>();
    }
    else
    {
        espgui::switchScreen<espvesc::MainScreen>();
    }

    /*--- Task Manager ---*/
    for (const auto& task : tasks)
        task.setup();

#if defined(CONFIG_ESP_TASK_WDT_PANIC) || defined(CONFIG_ESP_TASK_WDT)
    if (const auto result = esp_task_wdt_reset(); result != ESP_OK)
        ESP_LOGE(TAG, "esp_task_wdt_reset() failed with %s", esp_err_to_name(result));
#endif

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

