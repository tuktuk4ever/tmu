#pragma once

// local includes
#include "guihelpers/vescmenudisplay.h"

namespace espvesc {

class MainScreen : public VescMenuDisplay
{
    using Base = espgui::MenuDisplay;
public:
    MainScreen();

    std::string title() const override;

    void back() override;
};

} // namespace espvesc
