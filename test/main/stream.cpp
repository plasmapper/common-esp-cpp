#include "stream.h"
#include "unity.h"

//==============================================================================

const size_t bufferSize = 10;
const TickType_t readTimeout = 10;
size_t readableSize = 1;

//==============================================================================

void TestStream() {
  Stream stream;
  PL::Buffer buffer (10);
  uint8_t tempData[bufferSize];
  size_t tempDataSize;

  TEST_ASSERT (stream.Lock() == ESP_OK);

  TEST_ASSERT (stream.SetReadTimeout (readTimeout) == ESP_OK);
  TEST_ASSERT_EQUAL (readTimeout, stream.GetReadTimeout());
  TEST_ASSERT_EQUAL (readableSize, stream.GetReadableSize());

  TEST_ASSERT (stream.Read (tempData, bufferSize) == ESP_OK);
  for (size_t i = 0; i < bufferSize; i++)
    TEST_ASSERT (tempData[i] == i);

  stream.Reset();
  TEST_ASSERT (stream.Read (buffer, 0, bufferSize) == ESP_OK);
  for (size_t i = 0; i < bufferSize; i++)
    TEST_ASSERT (((uint8_t*)buffer.data)[i] == i);

  TEST_ASSERT (stream.Read (buffer, bufferSize, 1) == ESP_ERR_INVALID_ARG);
  TEST_ASSERT (stream.Read (buffer, 0, bufferSize + 1) == ESP_ERR_INVALID_SIZE);

  stream.Reset();
  TEST_ASSERT (stream.ReadUntil (tempData, bufferSize, bufferSize - 1, &tempDataSize) == ESP_OK);
  for (size_t i = 0; i < bufferSize; i++)
    TEST_ASSERT (tempData[i] == i);
  TEST_ASSERT (tempDataSize == bufferSize);

  stream.Reset();
  TEST_ASSERT (stream.ReadUntil (buffer, 0, bufferSize - 1, &tempDataSize) == ESP_OK);
  for (size_t i = 0; i < bufferSize; i++)
    TEST_ASSERT (((uint8_t*)buffer.data)[i] == i);
  TEST_ASSERT (tempDataSize == bufferSize);

  stream.Reset();
  TEST_ASSERT (stream.ReadUntil (buffer, bufferSize, 0, &tempDataSize) == ESP_ERR_INVALID_ARG);
  stream.Reset();
  TEST_ASSERT (stream.ReadUntil (buffer, 0, bufferSize, &tempDataSize) == ESP_ERR_INVALID_SIZE);

  stream.Reset();
  TEST_ASSERT (stream.ReadUntil (0xFF) == ESP_OK);

  TEST_ASSERT (stream.Write (tempData, bufferSize) == ESP_OK);
  TEST_ASSERT (stream.Write (buffer, 0, bufferSize) == ESP_OK);
  TEST_ASSERT (stream.Write ("Test") == ESP_OK);
  TEST_ASSERT (stream.Write (buffer, bufferSize, 1) == ESP_ERR_INVALID_ARG);
  TEST_ASSERT (stream.Write (buffer, 0, bufferSize + 1) == ESP_ERR_INVALID_SIZE);

  readableSize = 0;
  TEST_ASSERT (stream.FlushReadBuffer (5000 / portTICK_PERIOD_MS) == ESP_OK);

  TEST_ASSERT (stream.Unlock() == ESP_OK);
}

//==============================================================================

esp_err_t Stream::Lock (TickType_t timeout) {
  return mutex.Lock (timeout);
}

//==============================================================================

esp_err_t Stream::Unlock() {
  return mutex.Unlock();
}

//==============================================================================

esp_err_t Stream::Read (void* dest, size_t size) {
  PL::LockGuard lg (*this);
  for (size_t i = 0; i < size; i++)
    ((uint8_t*)dest)[i] = streamByte++;
  return ESP_OK;
}

//==============================================================================

esp_err_t Stream::Write (const void* src, size_t size) {
  PL::LockGuard lg (*this);
  return ESP_OK;
}

//==============================================================================

size_t Stream::GetReadableSize() {
  PL::LockGuard lg (*this);
  return readableSize;
}

//==============================================================================

TickType_t Stream::GetReadTimeout() {
  PL::LockGuard lg (*this);
  return readTimeout;
}

//==============================================================================

esp_err_t Stream::SetReadTimeout(TickType_t readTimeout) {
  PL::LockGuard lg (*this);
  this->readTimeout = readTimeout;
  return ESP_OK;
}

//==============================================================================

void Stream::Reset() {
  streamByte = 0;
}