#pragma once
#include "pl_lockable.h"

//==============================================================================

namespace PL {

//==============================================================================

/// @brief RAII-style lock guard class
class LockGuard {
public:
  /// @brief Lock the object with infinite timeout
  /// @param lockable lockable object
  LockGuard (Lockable& lockable);
  ~LockGuard ();
  LockGuard (const LockGuard&) = delete;
  LockGuard& operator= (const LockGuard&) = delete;

private:
  Lockable& lockable;
};

//==============================================================================

}