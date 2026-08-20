#pragma once
#include "freertos/FreeRTOS.h"

//==============================================================================

namespace PL {

//==============================================================================

/// @brief Lockable object class
class Lockable {
public:
  Lockable() = default;
  virtual ~Lockable() = default;
  Lockable(const Lockable&) = delete;
  Lockable& operator=(const Lockable&) = delete;

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