#include "pl_common.h"

//==============================================================================

class Server : public PL::Server {
public:
  esp_err_t Lock (TickType_t timeout = portMAX_DELAY) override;
  esp_err_t Unlock() override;
  esp_err_t Enable() override;
  esp_err_t Disable() override;

  bool IsEnabled() override;

private:
  PL::Mutex mutex;
  bool enabled = false;
};

//==============================================================================

class ServerEventHandler {
public:
  void OnServerEnabled (PL::Server& server);
  void OnServerDisabled (PL::Server& server);
  bool IsServerEnabled();

private:
  PL::Mutex mutex;
  bool serverEnabled = false;
};

//==============================================================================

void TestServer();