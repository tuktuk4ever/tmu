#pragma once

// 3rdparty lib includes
#include <display.h>

namespace espvesc {

class VescDisplay : public espgui::Display {
    using Base = espgui::Display;

public:
    void rawButtonPressed(uint8_t button) override;
    void rawButtonReleased(uint8_t button) override;
};

} // namespace espvesc
