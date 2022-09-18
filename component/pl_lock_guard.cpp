#include "pl_lock_guard.h"

//==============================================================================

namespace PL {

//==============================================================================

LockGuard::LockGuard (Lockable& lockable): lockable (lockable) {
  lockable.Lock();
}

//==============================================================================

LockGuard::~LockGuard () {
  lockable.Unlock();
}

//==============================================================================

}