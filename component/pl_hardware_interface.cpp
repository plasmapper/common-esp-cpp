#include "pl_hardware_interface.h"

//==============================================================================

namespace PL {

//==============================================================================

HardwareInterface::HardwareInterface() : enabledEvent(*this), disabledEvent(*this) {}

//==============================================================================

std::string HardwareInterface::GetName() {
  LockGuard lg(mutex);
  return name;
}

//==============================================================================

void HardwareInterface::SetName(const std::string& name) {
  LockGuard lg(mutex);
  this->name = name;
}

//==============================================================================

}