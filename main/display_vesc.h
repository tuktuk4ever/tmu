#pragma once

// 3rdparty lib includes
#include <widgets/label.h>

namespace espvesc::display {

extern espgui::Label bootLabel;

void set_boot_msg(std::string_view msg);

void tft_init_with_screen();

void go_back();

void init();

void update();

void redraw();

} // namespace espvesc::display
