#include "hardware_interface.h"
#include "unity.h"

//==============================================================================

const std::string interfaceName = "Interface name";

//==============================================================================

void TestHardwareInterface() {
  HardwareInterface interface;
  TEST_ASSERT (interface.Initialize() == ESP_OK);
  
  auto eventHandler = std::make_shared<HardwareInterfaceEventHandler>();
  interface.enabledEvent.AddHandler (eventHandler, &HardwareInterfaceEventHandler::OnHardwareInterfaceEnabled);
  interface.disabledEvent.AddHandler (eventHandler, &HardwareInterfaceEventHandler::OnHardwareInterfaceDisabled);

  TEST_ASSERT (interface.Enable() == ESP_OK);
  TEST_ASSERT (interface.IsEnabled());
  TEST_ASSERT (eventHandler->IsHardwareInterfaceEnabled());

  TEST_ASSERT (interface.Disable() == ESP_OK);
  TEST_ASSERT (!interface.IsEnabled());
  TEST_ASSERT (!eventHandler->IsHardwareInterfaceEnabled());

  interface.SetName (interfaceName);
  TEST_ASSERT (interface.GetName() == interfaceName);
}

//==============================================================================

esp_err_t HardwareInterface::Lock (TickType_t timeout) {
  return mutex.Lock (timeout);
}

//==============================================================================

esp_err_t HardwareInterface::Unlock() {
  return mutex.Unlock();
}

//==============================================================================

esp_err_t HardwareInterface::Initialize() {
  return ESP_OK;
}

//==============================================================================

esp_err_t HardwareInterface::Enable() {
  PL::LockGuard lg (*this);
  enabled = true;
  enabledEvent.Generate();
  return ESP_OK;
}

//==============================================================================

esp_err_t HardwareInterface::Disable() {
  PL::LockGuard lg (*this);
  enabled = false;
  disabledEvent.Generate();
  return ESP_OK;
}

//==============================================================================

bool HardwareInterface::IsEnabled() {
  PL::LockGuard lg (*this);
  return enabled;
}

//==============================================================================

void HardwareInterfaceEventHandler::OnHardwareInterfaceEnabled (PL::HardwareInterface& interface) {
  PL::LockGuard lg (mutex);
  hardwareInterfaceEnabled = true;
}

//==============================================================================

void HardwareInterfaceEventHandler::OnHardwareInterfaceDisabled (PL::HardwareInterface& interface) {
  PL::LockGuard lg (mutex);
  hardwareInterfaceEnabled = false;
}

//==============================================================================

bool HardwareInterfaceEventHandler::IsHardwareInterfaceEnabled() {
  PL::LockGuard lg (mutex);
  return hardwareInterfaceEnabled;
}