#include "pl_hardware_interface.h"

//==============================================================================

namespace PL {

//==============================================================================

HardwareInterface::HardwareInterface() : enabledEvent(*this), disabledEvent(*this) {}

//==============================================================================

std::string HardwareInterface::GetName() {
  LockGuard lg (*this);
  return name;
}

//==============================================================================

void HardwareInterface::SetName (const std::string& name) {
  LockGuard lg (*this);
  this->name = name;
}

//==============================================================================

}