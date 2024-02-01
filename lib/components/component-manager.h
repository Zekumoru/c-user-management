#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H

#define Component void

#include <stddef.h>
#include <stdbool.h>

/**
 * \brief Manages a list of components.
 */
typedef struct ComponentManager
{
  Component **components;
  size_t size;
  size_t allocSize;
  size_t indexFocusedComponent;
  void (*addComponent)(struct ComponentManager *cm, Component *component);
  bool (*focusComponent)(struct ComponentManager *cm, size_t index);
  void (*destroy)(struct ComponentManager *cm);
} ComponentManager;

/**
 * \brief Creates a new component manager.
 * \return A component manager.
 */
ComponentManager *createComponentManager();

#endif // COMPONENT_MANAGER_H
