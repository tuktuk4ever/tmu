#include "display_vesc.h"

constexpr const char * const TAG = "display";

// esp-idf includes
#include <esp_log.h>

// 3rdparty lib includes
#include <screenmanager.h>
#include <tftinterface.h>
#include <tftcolors.h>
#include <TFT_eSPI.h>
#include <color_utils.h>

// local includes
#include "screens/mainscreen.h"

namespace espvesc {

TFT_eSPI tft;

void display_init()
{
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_WHITE);

    espgui::switchScreen<MainScreen>();
}

void display_update()
{
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

void display_redraw()
{
    if (espgui::currentDisplay)
        espgui::currentDisplay->redraw(tft);
    else
        ESP_LOGW(TAG, "no current display to redraw");
}

} // namespace espvesc
