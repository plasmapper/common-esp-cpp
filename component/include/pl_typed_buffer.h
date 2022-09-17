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
  /// @brief typed buffer data
  Type data;

  /// @brief Create a typed buffer
  TypedBuffer() : Buffer (&data, sizeof (Type)) {}
};

//==============================================================================

}