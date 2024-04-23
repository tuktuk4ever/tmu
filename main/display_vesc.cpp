#include "display_vesc.h"

constexpr const char * const TAG = "display";

// esp-idf includes
#include <esp_log.h>

// 3rdparty lib includes
#include <screenmanager.h>
#include <tftcolors.h>
#include <TFT_eSPI.h>

// local includes
#include "utils/settings.h"

namespace espvesc::display {

espgui::Label bootLabel{16, 16};

TFT_eSPI tft;

void set_boot_msg(std::string_view msg)
{
    bootLabel.redraw(tft, msg, espgui::TFT_WHITE, espgui::TFT_BLACK, 4);
}

void init()
{
    tft.init();
    tft.setRotation(configs.displayRotated.value() ? 1 : 3);
    tft.fillScreen(TFT_WHITE);

    bootLabel.start(tft);
}

void tft_init_with_screen()
{
    if (espgui::currentDisplay)
        espgui::currentDisplay->initScreen(tft);
    else
        ESP_LOGW(TAG, "no current display to init");
}

void go_back()
{
    if (espgui::currentDisplay && espgui::displayStack.size() > 1)
        espgui::popScreen();
}

void update()
{
    if (tft.getRotation() != (configs.displayRotated.value() ? 1 : 3))
    {
        tft.setRotation(configs.displayRotated.value() ? 1 : 3);

        if (espgui::currentDisplay)
            espgui::currentDisplay->initScreen(tft);
    }

    if (espgui::currentDisplay)
        espgui::currentDisplay->update();
    else
        ESP_LOGW(TAG, "no current display to update");

    if (espgui::changeScreenCallback)
    {
        espgui::changeScreenCallback(tft);
        espgui::changeScreenCallback = nullptr;
    }
}

void redraw()
{
    if (espgui::currentDisplay)
        espgui::currentDisplay->redraw(tft);
    else
        ESP_LOGW(TAG, "no current display to redraw");
}

} // namespace espvesc::display
