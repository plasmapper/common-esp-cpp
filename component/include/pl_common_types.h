#pragma once
#include "freertos/FreeRTOS.h"

//==============================================================================

namespace PL {

//==============================================================================

/// @brief Task parameters
struct TaskParameters {
  /// @brief Task stack depth
  uint32_t stackDepth;
  /// @brief Task priority
  UBaseType_t priority;
  /// @brief Task CPU core ID
  BaseType_t coreId;
};

//==============================================================================

/// @brief Semantic version
struct SemanticVersion {
  /// @brief Major version
  uint16_t major;
  /// @brief Minor version
  uint16_t minor;
  /// @brief Patch version
  uint16_t patch;
};

//==============================================================================

}