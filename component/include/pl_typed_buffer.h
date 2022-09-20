#pragma once
#include "pl_buffer.h"

//==============================================================================

namespace PL {

//==============================================================================

/// @brief Class template for buffer with typed data member
/// @tparam Type data type
template <class Type>
class TypedBuffer : public Buffer {
public:
  /// @brief typed buffer data pointer
  Type* const data;

  /// @brief Create a typed buffer and allocate memory for its data
  TypedBuffer() : Buffer (new Type(), sizeof (Type)), data ((Type*)Buffer::data), preallocated (false) {}

  /// @brief Create a typed buffer with preallocated data
  /// @param data typed buffer data pointer
  TypedBuffer (Type* data) : Buffer (data, sizeof (Type)), data (data), preallocated (true)  {}

  /// @brief Create a typed buffer with preallocated data and shared lockable
  /// @param data typed buffer data pointer
  /// @param lockable lockable object that is locked when this typed buffer is locked
  TypedBuffer (Type* data, std::shared_ptr<Lockable> lockable) : Buffer (data, sizeof (Type), lockable), data (data), preallocated (true) {}

  ~TypedBuffer() {
    if (!preallocated)
      delete data;
  }
  TypedBuffer (const TypedBuffer&) = delete;
  TypedBuffer& operator= (const TypedBuffer&) = delete;

private:
  bool preallocated;
};

//==============================================================================

}