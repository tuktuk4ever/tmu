#include "vescmenudisplay.h"

// local includes
#include "control/buttons.h"
#include "display_vesc.h"

namespace espvesc {

void VescMenuDisplay::rawButtonPressed(uint8_t button)
{
    //Base::rawButtonPressed(button);
    if (const auto translated = translateRawButton(button))
        buttonPressed(*translated);
}

void VescMenuDisplay::rawButtonReleased(uint8_t button)
{
    //Base::rawButtonReleased(button);
    if (const auto translated = translateRawButton(button))
        buttonReleased(*translated);
}

void VescMenuDisplay::back()
{
    display::go_back();
}

} // namespace espvesc
