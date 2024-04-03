#include "mainscreen.h"

// 3rdparty lib includes
#include <menuitem.h>
#include <screenmanager.h>
#include <fmt/core.h>
#include <actions/dummyaction.h>

// local includes
#include "vesc.h"

namespace espvesc {

class VoltageText : public virtual espgui::TextInterface
{
public:
    std::string text() const override
    {
        const auto voltage = espvesc::getVescData().inpVoltage;

        return fmt::format("Voltage: {:.2f}", voltage);
    }
};

MainScreen::MainScreen()
{
    using namespace espgui;

    constructMenuItem<makeComponent<MenuItem, VoltageText, DummyAction>>();
}

std::string MainScreen::title() const
{
    return "Main Screen";
}

void MainScreen::back()
{
    espgui::popScreen();
}

} // namespace espvesc
