#pragma once
#include "pl_lockable.h"
#include <memory>

//==============================================================================

namespace PL {

//==============================================================================

/// @brief Lockable data buffer class
class Buffer : public Lockable {
public:
  /// @brief buffer data pointer
  void* const data;
  /// @brief buffer data size
  const size_t size;
  
  /// @brief Create a buffer with preallocated data and shared lockable
  /// @param data buffer data pointer
  /// @param size buffer data size
  /// @param lockable lockable object that is locked when this buffer is locked
  Buffer (void* data, size_t size, std::shared_ptr<Lockable> lockable);

  /// @brief Create a buffer with preallocated data
  /// @param data buffer data pointer
  /// @param size buffer data size
  Buffer (void* data, size_t size);

  /// @brief Create a buffer and allocate memory for its data
  /// @param size buffer data size
  Buffer (size_t size);
  ~Buffer ();
  Buffer (const Buffer&) = delete;
  Buffer& operator= (const Buffer&) = delete;

  esp_err_t Lock (TickType_t timeout = portMAX_DELAY) override;
  esp_err_t Unlock() override;

private:
  std::shared_ptr<Lockable> lockable;
  bool preallocated;
};

//==============================================================================

}