#include "lock.h"
#include "unity.h"

//==============================================================================

static PL::Mutex mutex;
bool endSingleLockTask = false;

static PL::Mutex multiLockMutex1, multiLockMutex2;
bool multiLockTask1Executed = false, multiLockTask2Executed = false;

//==============================================================================

void SingleLockTask(void* parameters) {
  mutex.Lock();
  while (!endSingleLockTask) {
    vTaskDelay(1);
  }
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  mutex.Unlock();
  vTaskDelete(NULL);
}

//==============================================================================

void MultiLockTask1(void* parameters) {
  {
    PL::LockGuard lg(multiLockMutex1, multiLockMutex2);
    multiLockTask1Executed = true;
  }
  vTaskDelete(NULL);
}

//==============================================================================

void MultiLockTask2(void* parameters) {
  {
    PL::LockGuard lg(multiLockMutex2, multiLockMutex1);
    multiLockTask2Executed = true;
  }
  vTaskDelete(NULL);
}

//==============================================================================

void TestLock() {
  // Unlocking without locking
  TEST_ASSERT(mutex.Unlock() == ESP_FAIL);

  // Recursive lock
  TEST_ASSERT(mutex.Lock() == ESP_OK);
  TEST_ASSERT(mutex.Lock() == ESP_OK);
  TEST_ASSERT(mutex.Unlock() == ESP_OK);
  TEST_ASSERT(mutex.Unlock() == ESP_OK);

  // LockGuard
  if (true) {
    PL::LockGuard lg(mutex);
  }

  TEST_ASSERT(xTaskCreate(SingleLockTask, "", 4096, NULL, tskIDLE_PRIORITY, NULL) == pdPASS);
  while (mutex.Lock(0) == ESP_OK) {
    mutex.Unlock();
    vTaskDelay(1);
  }
  endSingleLockTask = true;
  TEST_ASSERT(mutex.Lock() == ESP_OK);
  TEST_ASSERT(mutex.Unlock() == ESP_OK);

  // Multilock
  TEST_ASSERT(xTaskCreate(MultiLockTask1, "", 4096, NULL, tskIDLE_PRIORITY, NULL) == pdPASS);
  TEST_ASSERT(xTaskCreate(MultiLockTask2, "", 4096, NULL, tskIDLE_PRIORITY, NULL) == pdPASS);
  vTaskDelay(100 / portTICK_PERIOD_MS);
  TEST_ASSERT(multiLockTask1Executed);
  TEST_ASSERT(multiLockTask2Executed);
}