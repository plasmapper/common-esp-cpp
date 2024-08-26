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

  /// @brief Creates a typed buffer and allocates memory for its data
  TypedBuffer() : Buffer(new Type(), sizeof(Type)), data((Type*)Buffer::data), preallocated(false), isArray(false) {}

  /// @brief Creates a typed array buffer and allocates memory for its data
  /// @param arraySize array size
  TypedBuffer(size_t arraySize) : Buffer(new Type[arraySize], sizeof(Type) * arraySize), data((Type*)Buffer::data), preallocated(false), isArray(true) {}

  /// @brief Creates a typed buffer with preallocated data
  /// @param data typed buffer data pointer
  TypedBuffer(Type* data) : Buffer(data, sizeof(Type)), data(data), preallocated(true), isArray(false)  {}

  /// @brief Creates a typed array buffer with preallocated data
  /// @param data typed buffer data pointer
  /// @param arraySize array size
  TypedBuffer(Type* data, size_t arraySize) : Buffer(data, sizeof(Type) * arraySize), data(data), preallocated(true), isArray(true)  {}

  /// @brief Creates a typed buffer with preallocated data and shared lockable
  /// @param data typed buffer data pointer
  /// @param lockable lockable object that is locked when this typed buffer is locked
  TypedBuffer(Type* data, std::shared_ptr<Lockable> lockable) : Buffer(data, sizeof(Type), lockable), data(data), preallocated(true), isArray(false) {}

  /// @brief Creates a typed array buffer with preallocated data and shared lockable
  /// @param data typed buffer data pointer
  /// @param arraySize array size
  /// @param lockable lockable object that is locked when this typed buffer is locked
  TypedBuffer(Type* data, size_t arraySize, std::shared_ptr<Lockable> lockable) : Buffer(data, sizeof(Type) * arraySize, lockable), data(data), preallocated(true), isArray(true) {}

  ~TypedBuffer() {
    if (!preallocated) {
      if (isArray)
        delete[] data;
      else
        delete data;
    }      
  }
  TypedBuffer(const TypedBuffer&) = delete;
  TypedBuffer& operator=(const TypedBuffer&) = delete;

private:
  bool preallocated;
  bool isArray;
};

//==============================================================================

}