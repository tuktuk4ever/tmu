#pragma once

#include <sdkconfig.h>

#ifdef CONFIG_TUKTUK_BUTTON_TYPE_BASIC

// system includes
#include <array>

// local includes
#include "globals.h"

namespace buttons {

constexpr const std::array<pin_t, 4> IN_PINS = {
#ifdef CONFIG_TUKTUK_BASIC_PIN_1
        CONFIG_TUKTUK_BASIC_PIN_1,
#endif
#ifdef CONFIG_TUKTUK_BASIC_PIN_2
        CONFIG_TUKTUK_BASIC_PIN_2,
#endif
#ifdef CONFIG_TUKTUK_BASIC_PIN_3
        CONFIG_TUKTUK_BASIC_PIN_3,
#endif
#ifdef CONFIG_TUKTUK_BASIC_PIN_4
        CONFIG_TUKTUK_BASIC_PIN_4,
#endif
};

void init();
void update();
} // namespace buttons

#endif // CONFIG_TUKTUK_BUTTON_TYPE_BASIC
