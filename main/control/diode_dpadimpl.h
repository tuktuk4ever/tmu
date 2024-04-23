#pragma once

#include <sdkconfig.h>

#ifdef CONFIG_TUKTUK_BUTTON_TYPE_DIODE

// system includes
#include <array>
#include <cstdint>

// esp-idf includes
#include <esp32-hal-gpio.h>
#include <esp32-hal-misc.h>
#include <esp_log.h>

// 3rdparty lib includes
#include <espchrono.h>
#include <screenmanager.h>

// local includes
#include "globals.h"

using namespace std::chrono_literals;

struct Button {
    bool newState{false};
    bool lastState{false};
    espchrono::millis_clock::time_point debounce{espchrono::millis_clock::now()};
};

template<std::size_t Nin, std::size_t Nout, std::array<pin_t, Nin> pinsIn, std::array<pin_t, Nout> pinsOut>
class Dpad
{
private:
    std::array<Button, Nin * Nout * 2> m_buttons;

    void outPinModeAll(std::size_t mode);
public:
    Dpad() = default;

    void init();
    void update();
};

template<std::size_t Nin, std::size_t Nout, std::array<pin_t, Nin> pinsIn, std::array<pin_t, Nout> pinsOut>
void Dpad<Nin, Nout, pinsIn, pinsOut>::init()
{
    m_buttons.fill(Button{});
}

template<std::size_t Nin, std::size_t Nout, std::array<pin_t, Nin> pinsIn, std::array<pin_t, Nout> pinsOut>
void Dpad<Nin, Nout, pinsIn, pinsOut>::update()
{
    constexpr std::size_t num_buttons = Nin * Nout * 2;

    for (std::size_t outI = 0; outI < pinsOut.size(); outI++)
    {
        const auto pinOut = pinsOut[outI];
        outPinModeAll(INPUT);
        pinMode(pinOut, OUTPUT);

        digitalWrite(pinOut, LOW);

        delayMicroseconds(40);

        for (std::size_t inI = 0; inI < pinsIn.size(); inI++)
        {
            const auto pinIn = pinsIn[inI];
            const auto i = (outI * pinsIn.size() + inI) * 2;
            pinMode(pinIn, INPUT_PULLUP);

            delayMicroseconds(40);

            m_buttons[i].newState = !digitalRead(pinIn);
        }

        digitalWrite(pinOut, HIGH);

        delayMicroseconds(40);

        for (std::size_t inI = 0; inI < pinsIn.size(); inI++)
        {
            const auto pinIn = pinsIn[inI];
            const auto i = (outI * pinsIn.size() + inI) * 2;
            pinMode(pinIn, INPUT_PULLDOWN);

            delayMicroseconds(40);

            m_buttons[i+1].newState = digitalRead(pinIn);
        }
    }

    const auto now = espchrono::millis_clock::now();

    for (std::size_t i = 0; i < num_buttons; i++)
    {
        auto& button = m_buttons[i];

        if (button.lastState != button.newState && espchrono::ago(button.debounce) > 30ms)
        {
            button.lastState = button.newState;
            if (espgui::currentDisplay)
            {
                if (button.newState)
                    espgui::currentDisplay->rawButtonPressed(i);
                else
                    espgui::currentDisplay->rawButtonReleased(i);
            }
            button.debounce = now;
        }
    }
}

template<std::size_t Nin, std::size_t Nout, std::array<pin_t, Nin> pinsIn, std::array<pin_t, Nout> pinsOut>
void Dpad<Nin, Nout, pinsIn, pinsOut>::outPinModeAll(std::size_t mode)
{
    for (std::size_t pinOut = 0; pinOut < pinsOut.size(); pinOut++)
    {
        pinMode(pinsOut[pinOut], mode);
    }
}

#endif // CONFIG_TUKTUK_BUTTON_TYPE_DIODE
