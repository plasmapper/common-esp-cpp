#include "event.h"
#include "unity.h"

//==============================================================================

void TestEvent() {
  EventGenerator eventGenerator;
  auto eventHandler1 = std::make_shared<EventHandler1>();
  auto eventHandler2 = std::make_shared<EventHandler2>();
  eventGenerator.event.AddHandler (eventHandler1);
  eventGenerator.event.AddHandler (eventHandler2, &EventHandler2::EventHandlingFunction);
  // Check that same handler can be only added once to the event
  eventGenerator.event.AddHandler (eventHandler1);
  eventGenerator.event.AddHandler (eventHandler2, &EventHandler2::EventHandlingFunction);
  
  eventGenerator.EventGeneratingFunction();
  TEST_ASSERT(eventHandler1->GetLastEventGenerator() == &eventGenerator);
  TEST_ASSERT(eventHandler1->GetLastEventValue() == eventGenerator.GetLastEventValue());
  TEST_ASSERT(eventHandler1->GetNumberOfEventsHandled() == 1);
  TEST_ASSERT(eventHandler2->GetLastEventGenerator() == &eventGenerator);
  TEST_ASSERT(eventHandler2->GetLastEventValue() == eventGenerator.GetLastEventValue());
  TEST_ASSERT(eventHandler2->GetNumberOfEventsHandled() == 1);

  eventGenerator.event.RemoveHandler (eventHandler1);
  eventGenerator.EventGeneratingFunction();
  TEST_ASSERT(eventHandler1->GetLastEventValue() != eventGenerator.GetLastEventValue());
  TEST_ASSERT(eventHandler1->GetNumberOfEventsHandled() == 1);
  TEST_ASSERT(eventHandler2->GetLastEventValue() == eventGenerator.GetLastEventValue());
  TEST_ASSERT(eventHandler2->GetNumberOfEventsHandled() == 2);

  eventGenerator.event.RemoveHandler (eventHandler2, &EventHandler2::EventHandlingFunction);
  eventGenerator.EventGeneratingFunction();
  TEST_ASSERT(eventHandler2->GetLastEventValue() != eventGenerator.GetLastEventValue());
  TEST_ASSERT(eventHandler2->GetNumberOfEventsHandled() == 2);
}

//==============================================================================

EventGenerator::EventGenerator() : event (*this) {}

//==============================================================================

void EventGenerator::EventGeneratingFunction() {
  event.Generate (++lastEventValue);
}

//==============================================================================

int EventGenerator::GetLastEventValue() {
  return lastEventValue;
}

//==============================================================================

void EventHandler1::HandleEvent (EventGenerator& eventGenerator, int value) {
  lastEventGenerator = &eventGenerator;
  lastEventValue = value;
  numberOfEventsHandled++;
}

//==============================================================================

EventGenerator* EventHandler1::GetLastEventGenerator() {
  return lastEventGenerator;
}

//==============================================================================

int EventHandler1::GetLastEventValue() {
  return lastEventValue;
}

//==============================================================================

int EventHandler1::GetNumberOfEventsHandled() {
  return numberOfEventsHandled;
}

//==============================================================================

void EventHandler2::EventHandlingFunction (EventGenerator& eventGenerator, int value) {
  lastEventGenerator = &eventGenerator;
  lastEventValue = value;
  numberOfEventsHandled++;
}

//==============================================================================

EventGenerator* EventHandler2::GetLastEventGenerator() {
  return lastEventGenerator;
}

//==============================================================================

int EventHandler2::GetLastEventValue() {
  return lastEventValue;
}

//==============================================================================

int EventHandler2::GetNumberOfEventsHandled() {
  return numberOfEventsHandled;
}