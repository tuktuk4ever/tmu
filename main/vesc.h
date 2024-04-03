#pragma once

// 3rdparty lib includes
#include <VescUart.h>

namespace espvesc {

const dataPackage& getVescData();

void vesc_init();

} // namespace espvesc
