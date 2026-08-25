#include "pl_buffer.h"
#include "pl_mutex.h"
#include "pl_lock_guard.h"
#include "string.h"
#include "esp_check.h"

//==============================================================================

static const char* TAG = "pl_buffer";

//==============================================================================

namespace PL {

//==============================================================================

Buffer::Buffer(size_t size) : data(malloc(size)), size(size), lockable(std::make_shared<Mutex>()), preallocated(false) {
  if (!data) {
    ESP_LOGE(TAG, "allocation failed");
    abort();
  }
}

//==============================================================================

Buffer::Buffer(void* data, size_t size) : Buffer(data, size, std::make_shared<Mutex>()) {}

//==============================================================================

Buffer::Buffer(void* data, size_t size, std::shared_ptr<Lockable> lockable) : data(data), size(size), lockable(lockable), preallocated(true) {}

//==============================================================================

Buffer::~Buffer() {
  if (!preallocated)
    free((void*)data);
}

//==============================================================================

esp_err_t Buffer::Lock(TickType_t timeout) {
  esp_err_t error = lockable->Lock(timeout);
  if (error != ESP_OK && (error != ESP_ERR_TIMEOUT || timeout != 0))
    ESP_LOGE(TAG, "lock failed");
  return error;
}

//==============================================================================

esp_err_t Buffer::Unlock() {
  ESP_RETURN_ON_ERROR(lockable->Unlock(), TAG, "unlock failed");
  return ESP_OK;
}

//==============================================================================

void Buffer::Clear() {
  LockGuard lg(*this);
  memset(data, 0, size);
}

//==============================================================================

}