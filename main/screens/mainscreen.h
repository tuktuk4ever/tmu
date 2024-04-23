#pragma once

// local includes
#include "guihelpers/vescmenudisplay.h"

namespace espvesc {

class MainScreen : public VescMenuDisplay
{
    using Base = VescMenuDisplay;
public:
    MainScreen();

    std::string title() const override;
};

} // namespace espvesc
