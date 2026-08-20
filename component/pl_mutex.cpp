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
  if (xPortInIsrContext()) {
    ESP_DRAM_LOGE(TAG, "calling mutex lock from ISR");
    abort();
  }
  if (xSemaphoreTakeRecursive(mutex, timeout))
    return ESP_OK;
  if (timeout != 0)
    ESP_LOGE(TAG, "timeout");
  return ESP_ERR_TIMEOUT;
}

//==============================================================================

esp_err_t Mutex::Unlock() {
  if (xPortInIsrContext()) {
    ESP_DRAM_LOGE(TAG, "calling mutex unlock from ISR");
    abort();
  }
  ESP_RETURN_ON_FALSE(xSemaphoreGiveRecursive(mutex), ESP_FAIL, TAG, "semaphore give failed");
  return ESP_OK;
}

//==============================================================================

}