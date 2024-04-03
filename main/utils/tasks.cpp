#include "tasks.h"

constexpr const char * const TAG = "tasks";

// esp-idf includes
#include <esp_log.h>

// 3rdparty lib includes
#include <espchrono.h>

// local includes
#include "display_vesc.h"
#include "vesc.h"

namespace {

void noop() {}

using namespace espcpputils;
using namespace std::chrono_literals;

SchedulerTask tasksArray[]{
    SchedulerTask{"vesc_comm",      espvesc::vesc_init, noop,                     10s},
    SchedulerTask{"display_update", noop,               espvesc::display_update, 20ms},
    SchedulerTask{"display_redraw", noop,               espvesc::display_redraw, 16ms},
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
