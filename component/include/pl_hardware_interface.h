#pragma once
#include "pl_event.h"
#include "pl_stream.h"

//==============================================================================

namespace PL {

//==============================================================================

/// @brief Hardware interface class
class HardwareInterface : public virtual Lockable {
public:
  /// @brief hardware interface enabled event
  Event<HardwareInterface> enabledEvent;
  /// @brief hardware interface disabled event
  Event<HardwareInterface> disabledEvent;

  /// @brief Create a hardware interface
  HardwareInterface();

  /// @brief Initialize the hardware interface
  /// @return error code
  virtual esp_err_t Initialize() = 0;
   
  /// @brief Enable the hardware interface
  /// @return error code
  virtual esp_err_t Enable() = 0;
  /// @brief Disable the hardware interface
  /// @return error code
  virtual esp_err_t Disable() = 0;

  /// @brief Check if the hardware interface is enabled
  /// @return true if the hardware interface is enabled
  virtual bool IsEnabled() = 0;

  /// @brief Get the hardware interface name
  /// @return name
  std::string GetName();
  /// @brief Set the hardware interface name
  /// @param name 
  void SetName (const std::string& name);

private:
  std::string name;
};

//==============================================================================

}