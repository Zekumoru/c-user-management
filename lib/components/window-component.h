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
  Event *(*handleEvent)(Event *event);
} WindowComponent;

/**
 * \brief Create a new window component.
 * \return A window component.
 */
WindowComponent *createWindowComponent();

#endif // WINDOW_COMPONENT_H
