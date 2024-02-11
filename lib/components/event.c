#include "components.h"
#include <stdlib.h>
#include <string.h>

void destroyEvent_E(Event *event)
{
  free(event->name);
  free(event);
}

Event *createEvent(const char name[], Component *sender, EventPayload *payload)
{
  Event *event = malloc(sizeof(Event));
  event->name = strdup(name);
  event->sender = sender;
  event->payload = payload;
  event->destroy = destroyEvent_E;
  return event;
}
