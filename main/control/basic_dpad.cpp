#include "basic_dpad.h"

#include <sdkconfig.h>

#ifdef CONFIG_TUKTUK_BUTTON_TYPE_BASIC

constexpr const char * const TAG = "BASIC_DPAD";

// esp-idf includes
#include <driver/gpio.h>
#include <esp_log.h>

// 3rdparty lib includes
#include <espchrono.h>
#include <screenmanager.h>

namespace buttons {

using namespace std::chrono_literals;

struct Button {
    bool newState{false};
    bool lastState{false};
    espchrono::millis_clock::time_point debounce{espchrono::millis_clock::now()};
};

std::array<Button, IN_PINS.size()> button_states;

constexpr const bool HIGH_WHEN_ACTIVE =
#ifdef CONFIG_TUKTUK_BUTTON_TYPE_BASIC_INPUT_LEVEL_WHEN_PRESSED_HIGH
    true;
#elif defined(CONFIG_TUKTUK_BUTTON_TYPE_BASIC_INPUT_LEVEL_WHEN_PRESSED_LOW)
    false;
#endif

#if defined(CONFIG_TUKTUK_BUTTON_TYPE_BASIC_INPUT_MODE_PULLUP) && defined(CONFIG_TUKTUK_BUTTON_TYPE_BASIC_INPUT_LEVEL_WHEN_PRESSED_LOW)
#warning "Buttons set to PULLUP and LOW active level. Are you sure this is correct?"
#endif

#if defined(CONFIG_TUKTUK_BUTTON_TYPE_BASIC_INPUT_MODE_PULLDOWN) && defined(CONFIG_TUKTUK_BUTTON_TYPE_BASIC_INPUT_LEVEL_WHEN_PRESSED_HIGH)
#warning "Buttons set to PULLDOWN and HIGH active level. Are you sure this is correct?"
#endif

void init()
{
    for (auto pin : IN_PINS)
    {
        gpio_config_t io_conf{
            .pin_bit_mask = 1ULL << pin,
            .mode = GPIO_MODE_INPUT,
#if defined(CONFIG_TUKTUK_BUTTON_TYPE_BASIC_INPUT_MODE_NONE)
            .pull_up_en = GPIO_PULLUP_DISABLE,
            .pull_down_en = GPIO_PULLDOWN_DISABLE,
#elif defined(CONFIG_TUKTUK_BUTTON_TYPE_BASIC_INPUT_MODE_PULLUP)
            .pull_up_en = GPIO_PULLUP_ENABLE,
            .pull_down_en = GPIO_PULLDOWN_DISABLE,
#elif defined(CONFIG_TUKTUK_BUTTON_TYPE_BASIC_INPUT_MODE_PULLDOWN)
            .pull_up_en = GPIO_PULLUP_DISABLE,
            .pull_down_en = GPIO_PULLDOWN_ENABLE,
#endif
            .intr_type = GPIO_INTR_DISABLE,
        };
        gpio_config(&io_conf);
    }

    std::fill(std::begin(button_states), std::end(button_states), Button{});
}

void update()
{
    for (std::size_t i = 0; i < IN_PINS.size(); i++)
    {
        button_states[i].newState = gpio_get_level(static_cast<gpio_num_t>(IN_PINS[i])) != HIGH_WHEN_ACTIVE;
    }

    const auto now = espchrono::millis_clock::now();

    for (std::size_t i = 0; i < IN_PINS.size(); i++)
    {
        auto &button = button_states[i];

        if (button.newState != button.lastState && espchrono::ago(button.debounce) > 30ms)
        {
            ESP_LOGD(TAG, "Button %d: %s", IN_PINS[i], button.newState ? "pressed" : "released");

            button.lastState = button.newState;

            if (espgui::currentDisplay)
            {
                if (button.newState)
                    espgui::currentDisplay->rawButtonPressed(i);
                else
                    espgui::currentDisplay->rawButtonReleased(i);
            }

            button.debounce = now;
        }
    }
}

} // namespace buttons

#endif // CONFIG_TUKTUK_BUTTON_TYPE_BASIC
