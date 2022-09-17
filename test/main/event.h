#include "pl_common.h"

//==============================================================================

class EventGenerator {
public:
  PL::Event<EventGenerator, int> event;

  EventGenerator();

  void EventGeneratingFunction();
  int GetLastEventValue();

private:
  int lastEventValue = 0;
};

//==============================================================================

class EventHandler1 : public PL::EventHandler<EventGenerator, int> {
public:
  EventHandler1() {}

  void HandleEvent (EventGenerator& eventGenerator, int value) override;
  EventGenerator* GetLastEventGenerator();
  int GetLastEventValue();
  int GetNumberOfEventsHandled();

private:
  EventGenerator* lastEventGenerator = NULL;
  int lastEventValue = 0;
  int numberOfEventsHandled = 0;
};

//==============================================================================

class EventHandler2 {
public:
  EventHandler2() {}

  void EventHandlingFunction (EventGenerator& eventGenerator, int value);
  EventGenerator* GetLastEventGenerator();
  int GetLastEventValue();
  int GetNumberOfEventsHandled();

private:
  EventGenerator* lastEventGenerator = NULL;
  int lastEventValue = 0;
  int numberOfEventsHandled = 0;
};

//==============================================================================

void TestEvent();