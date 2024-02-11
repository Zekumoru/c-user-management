#ifndef WINDOW_MANAGER_COMPONENT_H
#define WINDOW_MANAGER_COMPONENT_H

#include "components.h"

/**
 * \brief A window manager component.
 *
 * Shows only one window (or component) at a time.
 * It's using ComponentManager under the hood treating windows like components
 * even though they're not. This is to avoid re-implementing the logic within
 * ComponentManager. (It could be a todo to handle the stack logic here instead)
 *
 */
typedef struct WindowManagerComponent
{
  ComponentPrototype *proto;
  ComponentManager *cm;
  void (*push)(struct WindowManagerComponent *, Window *);
  Window *(*pop)(struct WindowManagerComponent *);
} WindowManagerComponent;

/**
 * \brief Create a new window manager component.
 * \return A window manager component.
 */
WindowManagerComponent *createWindowManagerComponent();

#endif // WINDOW_MANAGER_COMPONENT_H
