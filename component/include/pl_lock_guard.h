#pragma once
#include "pl_lockable.h"

//==============================================================================

namespace PL {

//==============================================================================

/// @brief RAII-style lock guard class
class LockGuard {
public:
  /// @brief Locks the object with infinite timeout
  /// @param lockable lockable object
  LockGuard(Lockable& lockable);

  /// @brief Locks multiple objects with infinite timeout preventing deadlock
  /// @param lockable1 lockable object 1
  /// @param lockable1 lockable object 2
  LockGuard(Lockable& lockable1, Lockable& lockable2);

  /// @brief Locks multiple objects with infinite timeout preventing deadlock
  /// @param lockable1 lockable object 1
  /// @param lockable1 lockable object 2
  /// @param lockable1 lockable object 3
  LockGuard(Lockable& lockable1, Lockable& lockable2, Lockable& lockable3);

  ~LockGuard();
  LockGuard(const LockGuard&) = delete;
  LockGuard& operator=(const LockGuard&) = delete;

private:
  Lockable* lockable1 = NULL;
  Lockable* lockable2 = NULL;
  Lockable* lockable3 = NULL;
};

//==============================================================================

}