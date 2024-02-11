#ifndef WINDOW_COMPONENT_H
#define WINDOW_COMPONENT_H

#include "components.h"

/**
 * \brief A window component.
 *
 * This is more like a container to contain other components within it.
 *
 */
typedef struct WindowComponent
{
  ComponentPrototype *proto;
  ComponentManager *cm;
  Window *__window; // this is set by createWindowComponent function
  Event *(*handleEvent)(Window *window, Event *event);
} WindowComponent;

/**
 * \brief Create a new window component.
 * \return A window component.
 */
WindowComponent *createWindowComponent(Window *window);

#endif // WINDOW_COMPONENT_H
