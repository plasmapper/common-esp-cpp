#include "pl_stream.h"
#include "pl_lock_guard.h"
#include "esp_check.h"

//==============================================================================

static const char* TAG = "pl_stream";

//==============================================================================

namespace PL {

//==============================================================================

esp_err_t Stream::Read (Buffer& dest, size_t offset, size_t size) {
  LockGuard lg (dest);
  ESP_RETURN_ON_FALSE (offset < dest.size, ESP_ERR_INVALID_ARG, TAG, "invalid offset");
  ESP_RETURN_ON_FALSE (size <= dest.size - offset, ESP_ERR_INVALID_SIZE, TAG, "invalid size");
  ESP_RETURN_ON_ERROR (Read ((uint8_t*)dest.data + offset, size), TAG, "read failed");
  return ESP_OK;
}

//==============================================================================

esp_err_t Stream::ReadUntil (void* dest, size_t maxSize, char termChar, size_t* size) {
  LockGuard lg (*this);
  uint8_t byte;
  size_t tempSize = 0;
  for (; tempSize < maxSize; tempSize++) {
    ESP_RETURN_ON_ERROR (Read (&byte, 1), TAG, "read byte failed");
    if (dest)
      ((uint8_t*)dest)[tempSize] = byte;
    if (byte == termChar) {
      if (size)
        *size = tempSize + 1;
      return ESP_OK;
    } 
  }
  if (size)
    *size = tempSize;
  ESP_RETURN_ON_ERROR (ESP_ERR_INVALID_SIZE, TAG, "maxSize reached and no termChar read");
  return ESP_OK;
}

//==============================================================================

esp_err_t Stream::ReadUntil (Buffer& dest, size_t offset, char termChar, size_t* size) {
  LockGuard lg (dest);
  ESP_RETURN_ON_FALSE (offset < dest.size, ESP_ERR_INVALID_ARG, TAG, "invalid offset");
  ESP_RETURN_ON_ERROR (ReadUntil ((uint8_t*)dest.data + offset, dest.size - offset, termChar, size), TAG, "readUntil failed");
  return ESP_OK;
}

//==============================================================================

esp_err_t Stream::ReadUntil (char termChar) {
  return ReadUntil (NULL, SIZE_MAX, termChar, NULL);
}

//==============================================================================

esp_err_t Stream::Write (Buffer& src, size_t offset, size_t size) {
  LockGuard lg (src);
  ESP_RETURN_ON_FALSE (offset < src.size, ESP_ERR_INVALID_ARG, TAG, "invalid offset");
  ESP_RETURN_ON_FALSE (size <= src.size - offset, ESP_ERR_INVALID_SIZE, TAG, "invalid size");
  ESP_RETURN_ON_ERROR (Write ((uint8_t*)src.data + offset, size), TAG, "write failed");
  return ESP_OK;
}

//==============================================================================

esp_err_t Stream::Write (const std::string& src) {
  return Write (src.c_str(), src.size());
}

//==============================================================================

}