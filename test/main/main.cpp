#include "unity.h"
#include "buffer.h"
#include "event.h"
#include "hardware_interface.h"
#include "lock.h"
#include "server.h"
#include "stream.h"

//==============================================================================

extern "C" void app_main(void) {
  UNITY_BEGIN();
  RUN_TEST (TestBuffer);
  RUN_TEST (TestEvent);
  RUN_TEST (TestHardwareInterface);
  RUN_TEST (TestLock);
  RUN_TEST (TestServer);
  RUN_TEST (TestStream);
  UNITY_END();
}