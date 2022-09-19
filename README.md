# Common C++ Class Component for ESP-IDF

## Requirements
ESP-IDF 4.4 and higher.

## Installation
Add this to `main/idf_component.yml`:
```yaml
dependencies:
  pl_common:
    path: component
    git: https://github.com/plasmapper/common-esp-cpp.git
```
Add this to the source code:
```C++
#include "pl_common.h"
```

## Features
1. Mutex and lock guard class wrappers for FreeRTOS semaphores.
2. Lockable data buffer classes. 
3. Event and event handler classes.
4. Lockable stream class.
5. Base classes for hardware interface and server.

## Documentation
[Documentation](https://plasmapper.github.io/esp-cpp/common)
