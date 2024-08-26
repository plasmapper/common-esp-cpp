#include "pl_lock_guard.h"

//==============================================================================

namespace PL {

//==============================================================================

LockGuard::LockGuard(Lockable& lockable): lockable1(&lockable) {
  lockable.Lock();
}

//==============================================================================

LockGuard::LockGuard(Lockable& lockable1, Lockable& lockable2) : lockable1(&lockable1), lockable2(&lockable2) {
  while (1) {
    lockable1.Lock();
    if (lockable2.Lock(0) == ESP_OK)
      return;
    lockable1.Unlock();
    vTaskDelay(1);
  }
}

//==============================================================================

LockGuard::LockGuard(Lockable& lockable1, Lockable& lockable2, Lockable& lockable3) : lockable1(&lockable1), lockable2(&lockable2), lockable3(&lockable3) {
  while (1) {
    lockable1.Lock();
    if (lockable2.Lock(0) == ESP_OK) {
      if (lockable3.Lock(0) == ESP_OK)
        return;
      lockable2.Unlock();
    }
    lockable1.Unlock();
    vTaskDelay(1);
  }
}

//==============================================================================

LockGuard::~LockGuard() {
  if (lockable3)
    lockable3->Unlock();
  if (lockable2)
    lockable2->Unlock();
  if (lockable1)
    lockable1->Unlock();
}

//==============================================================================

}