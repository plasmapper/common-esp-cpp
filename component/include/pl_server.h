#pragma once
#include "pl_event.h"

//==============================================================================

namespace PL {

//==============================================================================

/// @brief Server class
class Server : public virtual Lockable {
public:
  /// @brief server enabled event
  Event<Server> enabledEvent;
  /// @brief server disabled event
  Event<Server> disabledEvent;

  /// @brief Creates a server
  Server();

  /// @brief Enables the server
  /// @return error code
  virtual esp_err_t Enable() = 0;
  
  /// @brief Disables the server
  /// @return error code
  virtual esp_err_t Disable() = 0;

  /// @brief Checks if the server is enabled
  /// @return true if the server is enabled
  virtual bool IsEnabled() = 0;

  /// @brief Gets the server name
  /// @return name
  std::string GetName();
  
  /// @brief Sets the server name
  /// @param name name
  void SetName(const std::string& name);

private:
  Mutex mutex;
  std::string name;
};


//==============================================================================

}