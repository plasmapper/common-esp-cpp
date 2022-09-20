Common Component
================

.. |COMPONENT| replace:: common

.. include:: ../../../installation.rst

.. include:: ../../../sdkconfig_common.rst

Features
--------

1. :cpp:class:`PL::Lockable` - a base class for any lockable object.
   Descendant classes should override :cpp:func:`PL::Lockable::Lock` and :cpp:func:`PL::Lockable::Unlock`.  
2. :cpp:class:`PL::LockGuard` - a RAII-style lock guard class.
   It is used to lock an object inside a code block: ``PL::LockGuard lg (PL::Lockable&);``.
3. :cpp:class:`PL::Mutex` - a mutex class.
   It inherits :cpp:class:`PL::Lockable` and overrides :cpp:func:`PL::Lockable::Lock` and :cpp:func:`PL::Lockable::Unlock`
   with FreeRTOS `xSemaphoreTakeRecursive` and `xSemaphoreGiveRecursive`.
4. :cpp:class:`PL::Buffer` - a lockable buffer class. The memory is either allocated when the buffer is initialized
   or the buffer uses an already preallocated data. Buffer also can be initialized with a shared lockable (for example when
   one buffer is a part of another buffer). PL::Buffer::data and :cpp:member:`PL::Buffer::size`.
5. :cpp:class:`PL::TypedBuffer` - a class template for a buffer with typed data. It inherits :cpp:class:`PL::Buffer` and
   has a typed public member :cpp:member:`PL::TypedBuffer::data`.
6. :cpp:class:`PL::Event` - an event class template. It can be added as a public member to the class and used by class member
   functions to generate events using :cpp:func:`PL::Event::Generate` and by external objects to subscribe/unsubscribe for events
   using :cpp:func:`PL::Event::AddHandler`/:cpp:func:`PL::Event::RemoveHandler`.
7. :cpp:class:`PL::EventHanler` - an event handler class template. If class handles only one event it can inherit this class and
   override :cpp:func:`PL::EventHanler::HandleEvent` method. For classes with multiple event handlers
   :cpp:func:`template<class HandlerClass> void PL::Event::AddHandler(std::shared_ptr<HandlerClass>, void(HandlerClass::*)(Source&, Args...))`
   should be used.
8. :cpp:class:`PL::Stream` - a base class for any stream. A number of :cpp:func:`PL::Stream::Read` and :cpp:func:`PL::Stream::Write`
   functions read and write to/from memory and :cpp:class:`PL::Buffer` objects. Reading and writing to/from :cpp:class:`PL::Buffer`
   object checks the data size and locks the object so these methods can be used in multithreaded applications.
9. :cpp:class:`PL::HardwareInterface` - a base class for any hardware interface. Descendant classes should override
   :cpp:func:`PL::HardwareInterface::Initialize`, :cpp:func:`PL::HardwareInterface::Enable`, :cpp:func:`PL::HardwareInterface::Disable`,
   :cpp:func:`PL::HardwareInterface::IsEnabled`, :cpp:func:`PL::HardwareInterface::Lock` and :cpp:func:`PL::HardwareInterface::Unlock`.
10. :cpp:class:`PL::Server` - a base class for any server. Descendant classes should override
    :cpp:func:`PL::Server::Enable`, :cpp:func:`PL::Server::Disable`,
    :cpp:func:`PL::Server::IsEnabled`, :cpp:func:`PL::Server::Lock` and :cpp:func:`PL::Server::Unlock`.


API reference
-------------

.. toctree::
  
  api/macros
  api/types      
  api/lockable
  api/lock_guard
  api/mutex
  api/buffer
  api/typed_buffer
  api/event
  api/event_handler
  api/stream
  api/hardware_interface
  api/server