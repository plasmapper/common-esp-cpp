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

  /// @brief Create a server
  Server();

  /// @brief Enable the server
  /// @return error code
  virtual esp_err_t Enable() = 0;
  
  /// @brief Disable the server
  /// @return error code
  virtual esp_err_t Disable() = 0;

  /// @brief Check if the server is enabled
  /// @return true if the server is enabled
  virtual bool IsEnabled() = 0;

  /// @brief Get the server name
  /// @return name
  std::string GetName();
  
  /// @brief Set the server name
  /// @param name name
  void SetName (const std::string& name);

private:
  std::string name;
};


//==============================================================================

}