#include "lock.h"
#include "unity.h"

//==============================================================================

static PL::Mutex mutex;
bool endTask = false;

//==============================================================================

void Task (void* parameters) {
  mutex.Lock();
  while (!endTask) {
    vTaskDelay(1);
  }
  vTaskDelay (1000 / portTICK_PERIOD_MS);
  mutex.Unlock();
  vTaskDelete (NULL);
}

//==============================================================================

void TestLock() {
  // Unlocking without locking
  TEST_ASSERT (mutex.Unlock() == ESP_FAIL);

  // Recursive lock
  TEST_ASSERT (mutex.Lock() == ESP_OK);
  TEST_ASSERT (mutex.Lock() == ESP_OK);
  TEST_ASSERT (mutex.Unlock() == ESP_OK);
  TEST_ASSERT (mutex.Unlock() == ESP_OK);

  // LockGuard
  if (true) {
    PL::LockGuard lg (mutex);
  }

  TEST_ASSERT (xTaskCreate (Task, "", 4096, NULL, tskIDLE_PRIORITY, NULL) == pdPASS);
  while (mutex.Lock(0) == ESP_OK) {
    mutex.Unlock();
    vTaskDelay(1);
  }
  endTask = true;
  TEST_ASSERT (mutex.Lock() == ESP_OK);
  TEST_ASSERT (mutex.Unlock() == ESP_OK);
}