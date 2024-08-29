#include "stream_server.h"
#include "unity.h"
#include "esp_check.h"

//==============================================================================

const uint8_t dataToSend[] = {1, 2, 3, 4, 5};
const uint8_t disableDataToSend[] = {0xFE, 0, 0, 0, 0};
const uint8_t restartDataToSend[] = {0xFF, 0, 0, 0, 0};
static uint8_t receivedData[sizeof(dataToSend)] = {};
static const char* TAG = "pl_stream_server_test";

//==============================================================================

void TestStreamServer() {
  auto stream1 = std::make_shared<StreamServerStream>();
  auto stream2 = std::make_shared<StreamServerStream>();

  StreamServer server(stream1);
  TEST_ASSERT(stream1 == server.GetStream());

  TEST_ASSERT(server.Enable() == ESP_OK);
  vTaskDelay(10);
  TEST_ASSERT(server.IsEnabled());
  TEST_ASSERT(stream1->Write(dataToSend, sizeof(dataToSend)) == ESP_OK);
  vTaskDelay(10);
  for (int i = 0; i < sizeof(dataToSend); i++)
    TEST_ASSERT_EQUAL(dataToSend[i], receivedData[i]);

  for (int i = 0; i < sizeof(dataToSend); i++)
    receivedData[i] = 0;
  TEST_ASSERT(server.SetStream(stream2) == ESP_OK);
  vTaskDelay(10);
  TEST_ASSERT(stream2 == server.GetStream());
  TEST_ASSERT(stream2->Write(dataToSend, sizeof(dataToSend)) == ESP_OK);
  vTaskDelay(10);
  for (int i = 0; i < sizeof(dataToSend); i++)
    TEST_ASSERT_EQUAL(dataToSend[i], receivedData[i]);

  // Test server disable and restart from request
  TEST_ASSERT(stream2->Write(disableDataToSend, sizeof(dataToSend)) == ESP_OK);
  vTaskDelay(10);
  TEST_ASSERT(!server.IsEnabled());

  TEST_ASSERT(server.Enable() == ESP_OK);
  TEST_ASSERT(server.IsEnabled());

  TEST_ASSERT(stream2->Write(restartDataToSend, sizeof(dataToSend)) == ESP_OK);
  vTaskDelay(10);
  TEST_ASSERT(server.IsEnabled());
  
  TEST_ASSERT(server.Disable() == ESP_OK);
  TEST_ASSERT(!server.IsEnabled());
}

//==============================================================================

esp_err_t StreamServerStream::Lock(TickType_t timeout) {
  esp_err_t error = mutex.Lock(timeout);
  if (error == ESP_OK)
    return ESP_OK;
  if (error == ESP_ERR_TIMEOUT && timeout == 0)
    return ESP_ERR_TIMEOUT;
  ESP_RETURN_ON_ERROR(error, TAG, "mutex lock failed");
  return ESP_OK;
}

//==============================================================================

esp_err_t StreamServerStream::Read(void* dest, size_t size) {
  PL::LockGuard lg(*this);
  if (size > buffer.size())
    return ESP_ERR_TIMEOUT;
  for (int i = 0; i < size; i++) {
    if (dest)
      ((uint8_t*)dest)[i] = buffer.front();
    buffer.pop_front();
  }
  return ESP_OK;
}

//==============================================================================

esp_err_t StreamServerStream::Write(const void* src, size_t size) {
  PL::LockGuard lg(*this);
  for (int i = 0; i < size; i++)
    buffer.push_back(((uint8_t*)src)[i]);
  return ESP_OK;
}

//==============================================================================

esp_err_t StreamServerStream::Unlock() {
  ESP_RETURN_ON_ERROR(mutex.Unlock(), TAG, "mutex unlock failed");
  return ESP_OK;
}

//==============================================================================

size_t StreamServerStream::GetReadableSize() {
  PL::LockGuard lg(*this);
  return buffer.size();
}

//==============================================================================

TickType_t StreamServerStream::GetReadTimeout() {
  return 0;
}

//==============================================================================

esp_err_t StreamServerStream::SetReadTimeout(TickType_t timeout) {
  return ESP_OK;
}

//==============================================================================

esp_err_t StreamServer::HandleRequest(PL::Stream& stream) {
  ESP_RETURN_ON_ERROR(stream.Read(receivedData, sizeof(receivedData)), TAG, "stream read failed");
  if (receivedData[0] == disableDataToSend[0])
    ESP_RETURN_ON_ERROR(Disable(), TAG, "server disable failed");
  if (receivedData[0] == restartDataToSend[0]) {
    ESP_RETURN_ON_ERROR(Disable(), TAG, "server disable failed");
    ESP_RETURN_ON_ERROR(Enable(), TAG, "server enable failed");
  }
  return ESP_OK;
}