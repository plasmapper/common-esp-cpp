#include "server.h"
#include "unity.h"

//==============================================================================

const std::string serverName = "Server name";

//==============================================================================

void TestServer() {
  Server server;
  auto eventHandler = std::make_shared<ServerEventHandler>();
  server.enabledEvent.AddHandler (eventHandler, &ServerEventHandler::OnServerEnabled);
  server.disabledEvent.AddHandler (eventHandler, &ServerEventHandler::OnServerDisabled);

  TEST_ASSERT (server.Lock() == ESP_OK);
  TEST_ASSERT (server.Unlock() == ESP_OK);

  TEST_ASSERT (server.Enable() == ESP_OK);
  TEST_ASSERT (server.IsEnabled());
  TEST_ASSERT (eventHandler->IsServerEnabled());

  TEST_ASSERT (server.Disable() == ESP_OK);
  TEST_ASSERT (!server.IsEnabled());
  TEST_ASSERT (!eventHandler->IsServerEnabled());

  server.SetName (serverName);
  TEST_ASSERT (server.GetName() == serverName);
}

//==============================================================================

esp_err_t Server::Lock (TickType_t timeout) {
  return mutex.Lock (timeout);
}

//==============================================================================

esp_err_t Server::Unlock() {
  return mutex.Unlock();
}

//==============================================================================

esp_err_t Server::Enable() {
  PL::LockGuard lg (*this);
  enabled = true;
  enabledEvent.Generate();
  return ESP_OK;
}

//==============================================================================

esp_err_t Server::Disable() {
  PL::LockGuard lg (*this);
  enabled = false;
  disabledEvent.Generate();
  return ESP_OK;
}

//==============================================================================

bool Server::IsEnabled() {
  PL::LockGuard lg (*this);
  return enabled;
}

//==============================================================================

void ServerEventHandler::OnServerEnabled (PL::Server& server) {
  PL::LockGuard lg (mutex);
  serverEnabled = true;
}

//==============================================================================

void ServerEventHandler::OnServerDisabled (PL::Server& server) {
  PL::LockGuard lg (mutex);
  serverEnabled = false;
}

//==============================================================================

bool ServerEventHandler::IsServerEnabled() {
  PL::LockGuard lg (mutex);
  return serverEnabled;
}