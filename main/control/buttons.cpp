#include "buttons.h"

// system includes
#include <optional>

// local includes
#include "utils/settings.h"

namespace {
constexpr const char * const TAG = "BUTTONS";
} // namespace

bool buttonsConfigured()
{
    return configs.dpadLeft.value() != INPUT_MAPPING_NONE &&
           configs.dpadRight.value() != INPUT_MAPPING_NONE &&
           configs.dpadUp.value() != INPUT_MAPPING_NONE &&
           configs.dpadDown.value() != INPUT_MAPPING_NONE;
}

[[nodiscard]] std::optional<espgui::Button> translateRawButton(uint8_t button)
{
    // Invalid
    if (button == INPUT_MAPPING_NONE)
    {
        return std::nullopt;
    }

    using espgui::Button;
    if (configs.dpadLeft.value() == button)
        return Button::Left;
    if (configs.dpadRight.value() == button)
        return Button::Right;
    if (configs.dpadUp.value() == button)
        return Button::Up;
    if (configs.dpadDown.value() == button)
        return Button::Down;

    return std::nullopt;
}

void buttonPressedCommon(espgui::Button button)
{
    /*
    switch (DisplayButton(button))
    {
        case DisplayButton::Left2:
        case DisplayButton::Right2:
        case DisplayButton::Up2:
        case DisplayButton::Down2:
            break;
        default:;
    }
    */
}

void buttonReleasedCommon(espgui::Button button)
{
    /*
    switch (BobbyButton(button))
    {
        case BobbyButton::Left2:
        case BobbyButton::Right2:
        case BobbyButton::Up2:
        case BobbyButton::Down2:
            break;
        default:;
    }
    */
}

void DisplayButtons::rawButtonPressed(uint8_t button)
{
    //Base::rawButtonPressed(button);
    if (const auto translated = translateRawButton(button))
    {
        buttonPressed(*translated);
    }
}

void DisplayButtons::rawButtonReleased(uint8_t button)
{
    //Base::rawButtonReleased(button);
    if (const auto translated = translateRawButton(button))
    {
        buttonReleased(*translated);
    }
}

void DisplayButtons::buttonPressed(espgui::Button button)
{
    //Base::buttonPressed(button);
    buttonPressedCommon(button);
}

void DisplayButtons::buttonReleased(espgui::Button button)
{
    //Base::buttonReleased(button);
    buttonReleasedCommon(button);
}
