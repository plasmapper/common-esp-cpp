#pragma once
#include "pl_mutex.h"
#include "pl_lock_guard.h"
#include "pl_event_handler.h"
#include <memory>
#include <vector>

//==============================================================================

namespace PL {

//==============================================================================

/// @brief Event class template
/// @tparam Source event source class 
/// @tparam ...Args event argument types
template <class Source, class... Args>
class Event {
public:
  /// @brief Creates an event
  /// @param source event source
  Event(Source& source) : source(source) {}
  ~Event() {}
  Event(const Event&) = delete;
  Event& operator=(const Event&) = delete;

  /// @brief Adds handler to the event
  /// @param handler event handler
  void AddHandler(std::shared_ptr<EventHandler<Source, Args...>> handler) {
    LockGuard lg(mutex);
    RemoveHandler(handler);
    handlers.push_back(handler);
  }

  /// @brief Adds handler to the event
  /// @tparam HandlerClass Event handler class
  /// @param handler Event handler object
  /// @param method Event handler object callback method
  template<class HandlerClass>
  void AddHandler(std::shared_ptr<HandlerClass> handler, void(HandlerClass::*method)(Source&, Args...)) {
    LockGuard lg(mutex);
    RemoveHandler(handler, method);
    auto methodHandler = std::make_shared<MethodEventHandler<HandlerClass>>(handler, method);
    methodHandlers.push_back(methodHandler);
    AddHandler(methodHandler);
  }

  /// @brief Removes handler from the event
  /// @param handlerToRemove event handler
  void RemoveHandler(std::shared_ptr<EventHandler<Source, Args...>> handlerToRemove) {
    LockGuard lg(mutex);
    for (auto handler = handlers.begin(); handler != handlers.end();) {
      bool handlerErased = false;
      if (auto handlerLocked = handler->lock()) {
        if (handlerLocked == handlerToRemove) {
          handlers.erase(handler);
          handlerErased = true;
        }
      }
      if (!handlerErased)
        handler++;
    }
  }

  /// @brief Removes handler from the event
  /// @tparam HandlerClass Event handler class
  /// @param handler Event handler object
  /// @param method Event handler object callback method
  template<class HandlerClass>
  void RemoveHandler(std::shared_ptr<HandlerClass> handlerToRemove, void(HandlerClass::*method)(Source&, Args...)) {
    LockGuard lg(mutex);
    for (auto handler = handlers.begin(); handler != handlers.end();) {
      bool handlerErased = false;
      if (auto handlerLocked = handler->lock()) {
        if (auto handlerCast = dynamic_cast<MethodEventHandler<HandlerClass>*>(handlerLocked.get())) {
          if (handlerToRemove == handlerCast->handler.lock() && method == handlerCast->method) {
            handlers.erase(handler);
            handlerErased = true;
          }
        }
      }
      if (!handlerErased)
        handler++;
    }
  }

  /// @brief Generates the event
  /// @param ...args event arguments
  void Generate(Args... args) {
    LockGuard lg(mutex);
    for (auto& handler : handlers) {
      if (auto lockedHandler = handler.lock())
        lockedHandler->HandleEvent(source, args...);
    }      
  }

private:
  Mutex mutex;
  Source& source;
  std::vector<std::weak_ptr<EventHandler<Source, Args...>>> handlers;
  std::vector<std::shared_ptr<EventHandler<Source, Args...>>> methodHandlers;

  template<class HandlerClass>
  class MethodEventHandler : public EventHandler<Source, Args...> {
  public:
    std::weak_ptr<HandlerClass> handler;
    void(HandlerClass::*method)(Source&, Args...);

    MethodEventHandler(std::shared_ptr<HandlerClass> handler, void(HandlerClass::*method)(Source&, Args...)) :
      handler(handler), method(method) {}
      
    void HandleEvent(Source& source, Args... args) override {
      if (auto handlerLocked = handler.lock())
        ((*handlerLocked).*method)(source, args...);
    }
  };
};

//==============================================================================

}