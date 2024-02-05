#ifndef WINDOW_MANAGER_COMPONENT_H
#define WINDOW_MANAGER_COMPONENT_H

#include "components.h"

/**
 * \brief A window manager component.
 *
 * Shows only one window (or component) at a time. Handling multiple windows
 * by using a stack where the top-most element is the component to render.
 *
 */
typedef struct WindowManagerComponent
{
  ComponentPrototype *proto;
  ComponentManager *cm;
  void (*push)(struct WindowManagerComponent *, Component *);
  void (*pop)(struct WindowManagerComponent *);
} WindowManagerComponent;

/**
 * \brief Create a new window manager component.
 * \return A window manager component.
 */
WindowManagerComponent *createWindowManagerComponent();

#endif // WINDOW_MANAGER_COMPONENT_H
