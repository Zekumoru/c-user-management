#include "components.h"
#include <stdlib.h>
#include <string.h>

void destroyEvent_E(Event *event)
{
  free(event->name);
  if (!event->persistsPayload && event->payload != NULL)
  {
    StubPayload *payload = (StubPayload *)event->payload;
    payload->destroy(payload);
  }
  free(event);
}

Event *cloneEvent_E(Event *event)
{
  Event *clone = malloc(sizeof(Event));
  clone->name = strdup(event->name);
  clone->sender = event->sender;
  clone->payload = event->payload;
  clone->persistsPayload = false;
  clone->clone = cloneEvent_E;
  clone->destroy = destroyEvent_E;
  return clone;
}

Event *createEvent(const char name[], Component *sender, EventPayload *payload)
{
  Event *event = malloc(sizeof(Event));
  event->name = strdup(name);
  event->sender = sender;
  event->payload = NULL;
  event->persistsPayload = false;
  event->clone = cloneEvent_E;
  event->destroy = destroyEvent_E;
  return event;
}

Event *createPersistentEvent(const char name[], Component *sender, EventPayload *payload)
{
  Event *event = createEvent(name, sender, payload);
  event->persistsPayload = true;
  return event;
}
