#include "pl_stream.h"
#include "pl_lock_guard.h"
#include "pl_common_macros.h"

//==============================================================================

namespace PL {

//==============================================================================

esp_err_t Stream::Read (Buffer& dest, size_t offset, size_t size) {
  LockGuard lg (dest);
  if (offset >= dest.size)
    return ESP_ERR_INVALID_ARG;
  if (size > dest.size - offset)
    return ESP_ERR_INVALID_SIZE;  
  return Read ((uint8_t*)dest.data + offset, size);
}

//==============================================================================

esp_err_t Stream::ReadUntil (void* dest, size_t maxSize, char termChar, size_t& size) {
  LockGuard lg (*this);
  uint8_t byte;
  for (size = 0; size < maxSize; ) {
    PL_RETURN_ON_ERROR (Read (&byte, 1));
    if (dest)
      ((uint8_t*)dest)[size++] = byte;
    if (byte == termChar)
      return ESP_OK;
  }
  return ESP_ERR_INVALID_SIZE;
}

//==============================================================================

esp_err_t Stream::ReadUntil (Buffer& dest, size_t offset, char termChar, size_t& size) {
  LockGuard lg (dest);
  if (offset >= dest.size)
    return ESP_ERR_INVALID_ARG;
  return ReadUntil ((uint8_t*)dest.data + offset, dest.size - offset, termChar, size);
}

//==============================================================================

esp_err_t Stream::ReadUntil (char termChar) {
  size_t size;
  return ReadUntil (NULL, SIZE_MAX, termChar, size);
}

//==============================================================================

esp_err_t Stream::Write (Buffer& src, size_t offset, size_t size) {
  LockGuard lg (src);
  if (offset >= src.size)
    return ESP_ERR_INVALID_ARG;
  if (size > src.size - offset)
    return ESP_ERR_INVALID_SIZE;
  return Write ((uint8_t*)src.data + offset, size);
}

//==============================================================================

}