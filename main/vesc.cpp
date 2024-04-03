#include "vesc.h"

constexpr const char * const TAG = "vesc_comm";

// esp-idf includes
#include <esp_log.h>

// 3rdparty lib includes
#include <VescUart.h>
#include <cleanuphelper.h>
#include <taskutils.h>

#include <espchrono.h>

namespace espvesc {

using namespace std::chrono_literals;

namespace {

VescUart vesc;

} // namespace

const dataPackage& getVescData()
{
    return vesc.getData();
}

void vesc_main_task(void*)
{
    uart_config_t uart_config = {
            .baud_rate = 115200,
            .data_bits = UART_DATA_8_BITS,
            .parity = UART_PARITY_DISABLE,
            .stop_bits = UART_STOP_BITS_1,
            .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    };

    vesc_uart_config_t vesc_uart_config = {
            .config = uart_config,
            .uart_num = UART_NUM_2,
            .tx_pin = 17,
            .rx_pin = 16,
    };

    vesc.setSerialPort(vesc_uart_config);

    auto lastTime = espchrono::millis_clock::now();

    while (true)
    {
        if (espchrono::ago(lastTime) > 250ms)
        {
            lastTime = espchrono::millis_clock::now();
            vesc.getVescValues();
        }

        vTaskDelay(1);
    }
}

void vesc_init()
{
    if (const auto res = espcpputils::createTask(vesc_main_task, "vesc_main_task", 4096, nullptr, 10, nullptr, espcpputils::CoreAffinity::Both); res != pdPASS)
    {
        ESP_LOGE(TAG, "Failed to create vesc_main_task: %s", esp_err_to_name(res));
    }
    else
    {
        ESP_LOGI(TAG, "vesc_main_task created");
    }
}

} // namespace espvesc
