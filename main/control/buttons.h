#pragma once

// system includes
#include <optional>

// 3rdparty lib includes
#include "buttonsinterface.h"

enum DisplayButton
{
    /*
    Left2 = espgui::Button::ButtonMax + 1,
    Right2,
    Up2,
    Down2,
    */
    Confirm = espgui::Button::Right,
    Back = espgui::Button::Left,
    ButtonMax = Back
};

bool buttonsConfigured();

[[nodiscard]] std::optional<espgui::Button> translateRawButton(uint8_t button);
void buttonPressedCommon(espgui::Button button);
void buttonReleasedCommon(espgui::Button button);

class DisplayButtons : public virtual espgui::ButtonsInterface
{
public:
    void rawButtonPressed(uint8_t button) override;
    void rawButtonReleased(uint8_t button) override;

    void buttonPressed(espgui::Button button) override;
    void buttonReleased(espgui::Button button) override;
};
