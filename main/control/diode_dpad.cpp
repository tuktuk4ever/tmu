#include "diode_dpad.h"

#include <sdkconfig.h>

#ifdef CONFIG_TUKTUK_BUTTON_TYPE_DIODE

namespace buttons {
Dpad<IN_PINS.size(), OUT_PINS.size(), IN_PINS, OUT_PINS> dpad;

void init()
{
    dpad.init();
}

void update()
{
    dpad.update();
}
} // namespace buttons

#endif // CONFIG_TUKTUK_BUTTON_TYPE_DIODE
