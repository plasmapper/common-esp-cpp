#pragma once
#include "freertos/FreeRTOS.h"

//==============================================================================

namespace PL {

//==============================================================================

/// @brief Task parameters
struct TaskParameters {
  /// @brief task stack depth
  uint32_t stackDepth;
  /// @brief task priority
  UBaseType_t priority;
  /// @brief task CPU core ID
  BaseType_t coreId;
};

//==============================================================================

}