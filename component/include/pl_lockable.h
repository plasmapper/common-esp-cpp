#pragma once
#include "freertos/FreeRTOS.h"

//==============================================================================

namespace PL {

//==============================================================================

/// @brief Lockable object class
class Lockable {
public:
  /// @brief Locks the object
  /// @param timeout timeout in FreeRTOS ticks
  /// @return error code 
  virtual esp_err_t Lock(TickType_t timeout = portMAX_DELAY) = 0;
  
  /// @brief Unlocks the object
  /// @return error code
  virtual esp_err_t Unlock() = 0;
};

//==============================================================================

}