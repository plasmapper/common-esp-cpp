#include "pl_common.h"

//==============================================================================

class Stream : public PL::Stream {
public:
  esp_err_t Lock(TickType_t timeout = portMAX_DELAY) override;
  esp_err_t Unlock() override;
  esp_err_t Read(void* dest, size_t size) override;
  using PL::Stream::Read;
  esp_err_t Write(const void* src, size_t size) override;
  using PL::Stream::Write;
  size_t GetReadableSize() override;
  TickType_t GetReadTimeout() override;
  esp_err_t SetReadTimeout(TickType_t readTimeout) override;
  TickType_t GetWriteTimeout() override;
  esp_err_t SetWriteTimeout(TickType_t writeTimeout) override;

  void Reset();

private:
  PL::Mutex mutex;
  uint8_t streamByte = 0;
  TickType_t readTimeout;
  TickType_t writeTimeout;
};

//==============================================================================

void TestStream();