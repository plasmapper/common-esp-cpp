#include "pl_common.h"

//==============================================================================

class HardwareInterface : public PL::HardwareInterface {
public:
  esp_err_t Lock(TickType_t timeout = portMAX_DELAY) override;
  esp_err_t Unlock() override;

  esp_err_t Initialize() override;
  esp_err_t Enable() override;
  esp_err_t Disable() override;

  bool IsEnabled() override;

private:
  PL::Mutex mutex;
  bool enabled = false;
};

//==============================================================================

class HardwareInterfaceEventHandler {
public:
  void OnHardwareInterfaceEnabled(PL::HardwareInterface& interface);
  void OnHardwareInterfaceDisabled(PL::HardwareInterface& interface);
  bool IsHardwareInterfaceEnabled();

private:
  PL::Mutex mutex;
  bool hardwareInterfaceEnabled = false;
};

//==============================================================================

void TestHardwareInterface();