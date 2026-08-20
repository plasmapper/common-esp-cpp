#include "pl_mutex.h"
#include "esp_check.h"
#include <cstdlib>

//==============================================================================

static const char* TAG = "pl_mutex";

//==============================================================================

namespace PL {

//==============================================================================

Mutex::Mutex() : mutex(xSemaphoreCreateRecursiveMutex()) {
  if (!mutex) {
    ESP_LOGE(TAG, "mutex creation failed");
    abort();
  }
}

//==============================================================================

Mutex::~Mutex() {
  vSemaphoreDelete(mutex);
}

//==============================================================================

esp_err_t Mutex::Lock(TickType_t timeout) {
  ESP_RETURN_ON_FALSE(!xPortInIsrContext(), ESP_ERR_INVALID_STATE, TAG, "calling mutex lock from ISR");
  if (xSemaphoreTakeRecursive(mutex, timeout))
    return ESP_OK;
  if (timeout != 0)
    ESP_LOGE(TAG, "timeout");
  return ESP_ERR_TIMEOUT;
}

//==============================================================================

esp_err_t Mutex::Unlock() {
  ESP_RETURN_ON_FALSE(!xPortInIsrContext(), ESP_ERR_INVALID_STATE, TAG, "calling mutex unlock from ISR");
  ESP_RETURN_ON_FALSE(xSemaphoreGiveRecursive(mutex), ESP_FAIL, TAG, "semaphore give failed");
  return ESP_OK;
}

//==============================================================================

}