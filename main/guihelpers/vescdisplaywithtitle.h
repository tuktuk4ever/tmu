#pragma once

// 3rdparty lib includes
#include <displaywithtitle.h>

namespace espvesc {

class VescDisplayWithTitle : public espgui::DisplayWithTitle
{
    using Base = espgui::DisplayWithTitle;

public:
    void rawButtonPressed(uint8_t button) override;
    void rawButtonReleased(uint8_t button) override;
};

} // namespace espvesc
