#pragma once
#include "freertos/FreeRTOS.h"

//==============================================================================

namespace PL {

//==============================================================================

/// @brief Lockable object class
class Lockable {
public:
  /// @brief Lock the object
  /// @param timeout timeout in FreeRTOS ticks
  /// @return error code 
  virtual esp_err_t Lock (TickType_t timeout = portMAX_DELAY) = 0;
  
  /// @brief Unlock the object
  /// @return error code
  virtual esp_err_t Unlock() = 0;
};

//==============================================================================

}