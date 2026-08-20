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
  EventHandler() = default;
  virtual ~EventHandler() = default;
  EventHandler(const EventHandler&) = delete;
  EventHandler& operator=(const EventHandler&) = delete;

  /// @brief Event handler callback method
  /// @param source event source
  /// @param ...args event arguments
  virtual void HandleEvent(Source& source, Args... args) = 0;
};

//==============================================================================

}