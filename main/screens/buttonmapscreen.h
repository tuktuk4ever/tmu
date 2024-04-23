#pragma once

// 3rdparty lib includes
#include <tftcolors.h>
#include <tftinterface.h>
#include <widgets/label.h>

// local includes
#include "guihelpers/vescdisplaywithtitle.h"

namespace espvesc {

namespace {

enum class CurrentButton : uint8_t {
    UP,
    RIGHT,
    DOWN,
    LEFT,
    CURRENT_BUTTON_MAX = LEFT
};

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    None
};

template<uint16_t x, uint16_t y>
class DrawDpad {
public:
    void start(espgui::TftInterface &tft);

    void redraw(espgui::TftInterface &tft, Direction highlight);

private:
    Direction m_last_direction{None};
};

template<uint16_t x, uint16_t y>
void DrawDpad<x, y>::start(espgui::TftInterface &tft)
{
    using namespace espgui;

    tft.drawCircle(x - 35, y, 20, espgui::TFT_WHITE);
    tft.drawCircle(x + 35, y, 20, espgui::TFT_WHITE);
    tft.drawCircle(x, y - 35, 20, espgui::TFT_WHITE);
    tft.drawCircle(x, y + 35, 20, espgui::TFT_WHITE);
}

template<uint16_t x, uint16_t y>
void DrawDpad<x, y>::redraw(espgui::TftInterface &tft, Direction highlight)
{
    using namespace espgui;

    tft.fillCircle(x - 35, y, 15, highlight == LEFT ? espgui::TFT_RED : espgui::TFT_BLACK);
    tft.fillCircle(x + 35, y, 15, highlight == RIGHT ? espgui::TFT_RED : espgui::TFT_BLACK);
    tft.fillCircle(x, y - 35, 15, highlight == UP ? espgui::TFT_RED : espgui::TFT_BLACK);
    tft.fillCircle(x, y + 35, 15, highlight == DOWN ? espgui::TFT_RED : espgui::TFT_BLACK);
}
} // namespace

class ButtonMapScreen : public VescDisplayWithTitle
{
    using Base = VescDisplayWithTitle;
public:
    void initScreen(espgui::TftInterface &tft) override;

    void update() override;

    void redraw(espgui::TftInterface &tft) override;

    std::string title() const override;

    void buttonPressed(espgui::Button button) override;
    void buttonReleased(espgui::Button button) override;

    void rawButtonPressed(uint8_t button) override;
    void rawButtonReleased(uint8_t button) override;

private:
    DrawDpad<70, 240 - 70> m_dpad_left;
    // DrawDpad<320 - 70, 240 - 70> m_dpad_right;

    espgui::Label m_label{25, 80};

    CurrentButton m_current_button{CurrentButton::UP};
};

} // namespace espvesc
