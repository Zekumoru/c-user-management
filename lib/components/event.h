#ifndef EVENT_H
#define EVENT_H

#include "components.h"
#include <stdbool.h>
#define EventPayload void

/**
 * \brief An event struct containing the name of the event, the payload, and
 *        the pointer to the event's invoker.
 * \warning Make sure the first field when creating a payload struct is the
 *          destroy method since this will be used for freeing the payload
 *          from memory.
 */
typedef struct Event
{
  char *name;
  Component *sender;
  EventPayload *payload;
  void (*destroy)(struct Event *event);
} Event;

/**
 * \brief Creates a new event.
 * \param name The name of the event.
 * \param payload Pointer to the extra data to pass in.
 * \return A new event.
 */
Event *createEvent(const char name[], Component *sender, EventPayload *payload);

#endif // EVENT_H
