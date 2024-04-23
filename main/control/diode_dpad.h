#pragma once

#include <sdkconfig.h>

#ifdef CONFIG_TUKTUK_BUTTON_TYPE_DIODE

// local includes
#include "diode_dpadimpl.h"
#include "globals.h"

namespace buttons {

constexpr const std::array<pin_t, CONFIG_TUKTUK_IN_PINS_COUNT> IN_PINS = {
#ifdef CONFIG_TUKTUK_IN_PIN_1
    CONFIG_TUKTUK_IN_PIN_1,
#endif
#ifdef CONFIG_TUKTUK_IN_PIN_2
    CONFIG_TUKTUK_IN_PIN_2,
#endif
#ifdef CONFIG_TUKTUK_IN_PIN_3
    CONFIG_TUKTUK_IN_PIN_3,
#endif
#ifdef CONFIG_TUKTUK_IN_PIN_4
    CONFIG_TUKTUK_IN_PIN_4,
#endif
#ifdef CONFIG_TUKTUK_IN_PIN_5
    CONFIG_TUKTUK_IN_PIN_5,
#endif
#ifdef CONFIG_TUKTUK_IN_PIN_6
    CONFIG_TUKTUK_IN_PIN_6,
#endif
#ifdef CONFIG_TUKTUK_IN_PIN_7
    CONFIG_TUKTUK_IN_PIN_7,
#endif
#ifdef CONFIG_TUKTUK_IN_PIN_8
    CONFIG_TUKTUK_IN_PIN_8,
#endif
};

constexpr const std::array<pin_t, CONFIG_TUKTUK_OUT_PINS_COUNT> OUT_PINS = {
#ifdef CONFIG_TUKTUK_OUT_PIN_1
    CONFIG_TUKTUK_OUT_PIN_1,
#endif
#ifdef CONFIG_TUKTUK_OUT_PIN_2
    CONFIG_TUKTUK_OUT_PIN_2,
#endif
#ifdef CONFIG_TUKTUK_OUT_PIN_3
    CONFIG_TUKTUK_OUT_PIN_3,
#endif
#ifdef CONFIG_TUKTUK_OUT_PIN_4
    CONFIG_TUKTUK_OUT_PIN_4,
#endif
#ifdef CONFIG_TUKTUK_OUT_PIN_5
    CONFIG_TUKTUK_OUT_PIN_5,
#endif
#ifdef CONFIG_TUKTUK_OUT_PIN_6
    CONFIG_TUKTUK_OUT_PIN_6,
#endif
#ifdef CONFIG_TUKTUK_OUT_PIN_7
    CONFIG_TUKTUK_OUT_PIN_7,
#endif
#ifdef CONFIG_TUKTUK_OUT_PIN_8
    CONFIG_TUKTUK_OUT_PIN_8,
#endif
};

extern Dpad<IN_PINS.size(), OUT_PINS.size(), IN_PINS, OUT_PINS> dpad;

void init();
void update();
} // namespace buttons

#endif // CONFIG_TUKTUK_BUTTON_TYPE_DIODE
