#include "vescdisplaywithtitle.h"

// local includes
#include "control/buttons.h"

namespace espvesc {

void VescDisplayWithTitle::rawButtonPressed(uint8_t button)
{
    //Base::rawButtonPressed(button);
    if (const auto translated = translateRawButton(button))
        buttonPressed(*translated);
}

void VescDisplayWithTitle::rawButtonReleased(uint8_t button)
{
    //Base::rawButtonReleased(button);
    if (const auto translated = translateRawButton(button))
        buttonReleased(*translated);
}

} // namespace espvesc
