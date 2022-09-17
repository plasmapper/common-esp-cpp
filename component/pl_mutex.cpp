#include "pl_mutex.h"

//==============================================================================

namespace PL {

//==============================================================================

Mutex::Mutex () : mutex (xSemaphoreCreateRecursiveMutex()) {}

//==============================================================================

Mutex::~Mutex () {
  if (mutex)
    vSemaphoreDelete(mutex);
}

//==============================================================================

esp_err_t Mutex::Lock (TickType_t timeout) {
  if (!mutex || xPortInIsrContext())
    return ESP_ERR_INVALID_STATE;
  return (xSemaphoreTakeRecursive (mutex, timeout))?(ESP_OK):(ESP_ERR_TIMEOUT);
}

//==============================================================================

esp_err_t Mutex::Unlock() {
  if (!mutex || xPortInIsrContext())
    return ESP_ERR_INVALID_STATE;
  return (xSemaphoreGiveRecursive (mutex))?(ESP_OK):(ESP_FAIL);
}

//==============================================================================

}