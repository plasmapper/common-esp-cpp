#include "pl_lock_guard.h"
#include "freertos/task.h"

//==============================================================================

namespace PL {

//==============================================================================

LockGuard::LockGuard(Lockable& lockable, TickType_t timeout) {
  if (lockable.Lock(timeout) == ESP_OK)
    lockable1 = &lockable;
}

//==============================================================================

LockGuard::LockGuard(Lockable& lockable1, Lockable& lockable2, TickType_t timeout) {
  TimeOut_t timeOut;
  vTaskSetTimeOutState(&timeOut);
  TickType_t remainingTimeout = timeout;

  while (1) {
    if (lockable1.Lock(remainingTimeout) != ESP_OK)
      return;

    esp_err_t error = lockable2.Lock(0);
    if (error == ESP_OK) {
      this->lockable1 = &lockable1;
      this->lockable2 = &lockable2;
      return;
    }

    lockable1.Unlock();
    if (error != ESP_ERR_TIMEOUT || xTaskCheckForTimeOut(&timeOut, &remainingTimeout) != pdFALSE)
      return;
    vTaskDelay(1);
  }
}

//==============================================================================

LockGuard::LockGuard(Lockable& lockable1, Lockable& lockable2, Lockable& lockable3, TickType_t timeout) {
  TimeOut_t timeOut;
  vTaskSetTimeOutState(&timeOut);
  TickType_t remainingTimeout = timeout;

  while (1) {
    if (lockable1.Lock(remainingTimeout) != ESP_OK)
      return;

    esp_err_t error = lockable2.Lock(0);
    if (error == ESP_OK) {
      error = lockable3.Lock(0);
      if (error == ESP_OK) {
        this->lockable1 = &lockable1;
        this->lockable2 = &lockable2;
        this->lockable3 = &lockable3;
        return;
      }
      lockable2.Unlock();
    }

    lockable1.Unlock();
    if (error != ESP_ERR_TIMEOUT || xTaskCheckForTimeOut(&timeOut, &remainingTimeout) != pdFALSE)
      return;
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

bool LockGuard::IsLocked() const {
  return lockable1;
}

//==============================================================================

}