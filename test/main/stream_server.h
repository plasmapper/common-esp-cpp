#include "pl_mutex.h"
#include "pl_stream.h"
#include "pl_stream_server.h"
#include <list>

//==============================================================================

class StreamServerStream : public PL::Stream {
public:
  using PL::Stream::Stream;
  esp_err_t Lock(TickType_t timeout = portMAX_DELAY) override;
  esp_err_t Unlock() override;
  esp_err_t Read(void* dest, size_t size) override;
  esp_err_t Write(const void* src, size_t size) override;
  size_t GetReadableSize() override;
  TickType_t GetReadTimeout() override;
  esp_err_t SetReadTimeout(TickType_t timeout) override;

private:
  PL::Mutex mutex;
  std::list<uint8_t> buffer;
};

//==============================================================================

class StreamServer : public PL::StreamServer {
public:
  using PL::StreamServer::StreamServer;
  esp_err_t HandleRequest(PL::Stream& stream) override;
};

//==============================================================================

void TestStreamServer();