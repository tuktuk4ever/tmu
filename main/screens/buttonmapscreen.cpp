#include "buttonmapscreen.h"

constexpr const char * const TAG = "BUTTON_CALIBRATION";

// esp-idf includes
#include <esp_log.h>

// 3rdparty lib includes
#include <screenmanager.h>

// local includes
#include "screens/mainscreen.h"
#include "utils/settings.h"

namespace espvesc {

void ButtonMapScreen::initScreen(espgui::TftInterface &tft)
{
    using namespace espgui;

    Base::initScreen(tft);

    m_dpad_left.start(tft);
    // m_dpad_right.start();

    m_label.start(tft);
}

void ButtonMapScreen::update()
{
    Base::update();
}

void ButtonMapScreen::redraw(espgui::TftInterface &tft)
{
    Base::redraw(tft);

    switch (m_current_button)
    {
    case CurrentButton::UP:
        m_dpad_left.redraw(tft, UP);
        // m_dpad_right.redraw(None);
        break;
    case CurrentButton::RIGHT:
        m_dpad_left.redraw(tft, RIGHT);
        // m_dpad_right.redraw(None);
        break;
    case CurrentButton::DOWN:
        m_dpad_left.redraw(tft, DOWN);
        // m_dpad_right.redraw(None);
        break;
    case CurrentButton::LEFT:
        m_dpad_left.redraw(tft, LEFT);
        // m_dpad_right.redraw(None);
        break;
    /*
    case 4:
        m_dpad_left.redraw(None);
        m_dpad_right.redraw(UP);
        break;
    case 5:
        m_dpad_left.redraw(None);
        m_dpad_right.redraw(RIGHT);
        break;
    case 6:
        m_dpad_left.redraw(None);
        m_dpad_right.redraw(DOWN);
        break;
    case 7:
        m_dpad_left.redraw(None);
        m_dpad_right.redraw(LEFT);
        break;
    */
    default:
        m_dpad_left.redraw(tft, None);
        // m_dpad_right.redraw(None);

        m_label.redraw(tft, "Press RIGHT to continue", espgui::TFT_WHITE, espgui::TFT_BLACK, 2);
        break;
    }
}

void ButtonMapScreen::buttonPressed(espgui::Button button)
{
    ESP_LOGI(TAG, "Button %d pressed", std::to_underlying(button));
    // Base::buttonPressed(button);
    if (m_current_button < CurrentButton::CURRENT_BUTTON_MAX)
    {
        ESP_LOGI(TAG, "m_current_button < 3");
        return;
    }

    if (button == espgui::Button::Right)
    {
        espgui::switchScreen<MainScreen>();
    }
}

void ButtonMapScreen::buttonReleased(espgui::Button button)
{
    // Base::buttonReleased(button);
}

void ButtonMapScreen::rawButtonPressed(uint8_t button)
{
    // Base::rawButtonPressed(button);
    switch (m_current_button)
    {
    case CurrentButton::UP:
        if (const auto res = configs.write_config(configs.dpadUp, button); !res)
        {
            ESP_LOGE(TAG, "Failed to write config: %s", res.error().c_str());
            return;
        }
        break;
    case CurrentButton::RIGHT:
        if (const auto res = configs.write_config(configs.dpadRight, button); !res)
        {
            ESP_LOGE(TAG, "Failed to write config: %s", res.error().c_str());
            return;
        }
        break;
    case CurrentButton::DOWN:
        if (const auto res = configs.write_config(configs.dpadDown, button); !res)
        {
            ESP_LOGE(TAG, "Failed to write config: %s", res.error().c_str());
            return;
        }
        break;
    case CurrentButton::LEFT:
        if (const auto res = configs.write_config(configs.dpadLeft, button); !res)
        {
            ESP_LOGE(TAG, "Failed to write config: %s", res.error().c_str());
            return;
        }
        break;
    /*
    case 4:
        if (const auto res = configs.write_config(configs.dpadUp2, button); !res) {
            ESP_LOGE(TAG, "Failed to write config: %s", res.error().c_str());
            return;
        }
        m_current_button++;
        break;
    case 5:
        if (const auto res = configs.write_config(configs.dpadRight2, button); !res) {
            ESP_LOGE(TAG, "Failed to write config: %s", res.error().c_str());
            return;
        }
        m_current_button++;
        break;
    case 6:
        if (const auto res = configs.write_config(configs.dpadDown2, button); !res) {
            ESP_LOGE(TAG, "Failed to write config: %s", res.error().c_str());
            return;
        }
        m_current_button++;
        break;
    case 7:
        if (const auto res = configs.write_config(configs.dpadLeft2, button); !res) {
            ESP_LOGE(TAG, "Failed to write config: %s", res.error().c_str());
            return;
        }
        m_current_button++;
        break;
    */
    default:
        break;
    }

    m_current_button = static_cast<CurrentButton>(std::to_underlying(m_current_button) + 1);

    Base::rawButtonPressed(button);
}

void ButtonMapScreen::rawButtonReleased(uint8_t button)
{
    // Base::rawButtonReleased(button);
}

std::string ButtonMapScreen::title() const
{
    return "Button Mapping";
}

} // namespace espvesc
