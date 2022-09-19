#include "pl_buffer.h"
#include "pl_mutex.h"

//==============================================================================

namespace PL {

//==============================================================================

Buffer::Buffer (size_t size) : data (malloc (size)), size (size), lockable (std::make_shared<Mutex>()), preallocated (false) {}

//==============================================================================

Buffer::Buffer (void* data, size_t size) : Buffer (data, size, std::make_shared<Mutex>()) {}

//==============================================================================

Buffer::Buffer (void* data, size_t size, std::shared_ptr<Lockable> lockable) : data (data), size (size), lockable (lockable), preallocated (true) {}

//==============================================================================

Buffer::~Buffer() {
  if (!preallocated)
    free ((void*)data);
}

//==============================================================================

esp_err_t Buffer::Lock (TickType_t timeout) {
  return lockable->Lock (timeout);
}

//==============================================================================

esp_err_t Buffer::Unlock() {
  return lockable->Unlock();
}

//==============================================================================

}