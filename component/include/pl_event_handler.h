#pragma once

//==============================================================================

namespace PL {

//==============================================================================

/// @brief Event handler class template
/// @tparam Source event source class
/// @tparam ...Args event argument types
template <class Source, class... Args>
class EventHandler {
public:
  /// @brief Event handler callback method
  /// @param source event source
  /// @param ...args event arguments
  virtual void HandleEvent(Source& source, Args... args) = 0;
};

//==============================================================================

}