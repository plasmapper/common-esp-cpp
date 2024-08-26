#pragma once
#include "pl_lockable.h"
#include "freertos/semphr.h"

//==============================================================================

namespace PL {

//==============================================================================

/// @brief Mutex class
class Mutex : public Lockable {
public:
  /// @brief Creates a mutex
  Mutex();
  ~Mutex();
  Mutex(const Mutex&) = delete;
  Mutex& operator=(const Mutex&) = delete;

  esp_err_t Lock(TickType_t timeout = portMAX_DELAY) override;
  esp_err_t Unlock() override;

private:
  SemaphoreHandle_t mutex;
};

//==============================================================================

}