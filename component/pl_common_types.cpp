#include "pl_common_types.h"

//==============================================================================

namespace PL {

//==============================================================================

bool TaskParameters::operator==(const TaskParameters& other) const {
  return stackDepth == other.stackDepth && priority == other.priority && coreId == other.coreId;
}

//==============================================================================

bool TaskParameters::operator!=(const TaskParameters& other) const {
  return !(*this == other);
}

//==============================================================================

}
