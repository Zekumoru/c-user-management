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
} ComponentManager;

/**
 * \brief Creates a new component manager.
 * \return A component manager.
 */
ComponentManager *createComponentManager();

/**
 * \brief Frees a component manager from memory.
 * \param cm A component manager to free.
 */
void destroyComponentManager(ComponentManager *cm);

/**
 * \brief Adds a new component to a component manager.
 * \param cm The component manager.
 * \param component The new component to add to the list.
 */
void addComponent(ComponentManager *cm, Component *component);

/**
 * \brief Sets the focus of a component.
 * \param cm The component manager.
 * \param index Index of the component to focus.
 * \return A boolean denoting if the component has been focused.
 */
bool focusComponent(ComponentManager *cm, size_t index);

#endif // COMPONENT_MANAGER_H
