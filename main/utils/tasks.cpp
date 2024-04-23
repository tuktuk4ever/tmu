#include "tasks.h"

constexpr const char * const TAG = "tasks";

// esp-idf includes
#include <esp_log.h>

// 3rdparty lib includes
#include <espchrono.h>

// local includes
#include "debuginputhandler.h"
#include "display_vesc.h"
#include "vesc.h"

// optional local includes
#ifdef CONFIG_TUKTUK_BUTTON_TYPE_DIODE
#include "control/diode_dpad.h"
#endif
#ifdef CONFIG_TUKTUK_BUTTON_TYPE_BASIC
#include "control/basic_dpad.h"
#endif

namespace {

void noop() {}

using namespace espcpputils;
using namespace std::chrono_literals;

SchedulerTask tasksArray[]{
    SchedulerTask{"debugconsole",   espvesc::initDebugInput, espvesc::handleDebugInput, 50ms},
    SchedulerTask{"vesc_comm",      espvesc::vesc_init,      noop,                       10s},
    SchedulerTask{"display_update", noop,                    espvesc::display::update,  20ms},
    SchedulerTask{"display_redraw", noop,                    espvesc::display::redraw,  16ms},
#ifdef CONFIG_TUKTUK_BUTTON_TYPE_DIODE
    SchedulerTask{"diode_dpad",     buttons::init,           buttons::update,           30ms},
#endif
#ifdef CONFIG_TUKTUK_BUTTON_TYPE_BASIC
    SchedulerTask{"basic_dpad",     buttons::init,           buttons::update,           30ms},
#endif
};

} // namespace

cpputils::ArrayView<espcpputils::SchedulerTask> tasks{tasksArray};

void sched_pushStats(bool printTasks)
{
    if (printTasks)
        ESP_LOGI(TAG, "begin listing tasks...");

    for (auto &task : tasks)
        task.pushStats(printTasks);

    if (printTasks)
        ESP_LOGI(TAG, "end listing tasks");
}
