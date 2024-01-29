#ifndef COMPONENTS_COMPONENTS_H
#define COMPONENTS_COMPONENTS_H

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
 * \brief A struct which all components "inherits" from.
 */
typedef struct ComponentPrototype
{
  char *type;
  bool focusable;
  void (*logic)(Component *, int);
  void (*render)(Component *);
  void (*delete)(Component *);
} ComponentPrototype;

/**
 * \brief Creates a new component prototype.
 * \return A component prototype.
 */
ComponentPrototype *createComponentPrototype();

/**
 * \brief Frees a component prototype.
 * \param proto A pointer to the component prototype to free.
 */
void destroyComponentPrototype(ComponentPrototype *proto);

/**
 * \brief A struct to denote an unknown component.
 */
typedef struct StubComponent
{
  ComponentPrototype *proto;
} StubComponent;

/**
 * \brief A header component.
 */
typedef struct HeaderComponent
{
  ComponentPrototype *proto;
  char *text;
} HeaderComponent;

/**
 * \brief Logic code for header component.
 * \param hc A header component.
 */
void logicHeaderComponent(Component *_hc, int charInput);

/**
 * \brief Render code for header component.
 * \param hc A header component to render.
 */
void renderHeaderComponent(Component *_hc);

/**
 * \brief Frees a header component from memory.
 * \param tic A header component to free.
 */
void deleteHeaderComponent(Component *_hc);

/**
 * \brief Creates a new header component.
 * \return A header component.
 */
HeaderComponent *createHeaderComponent();

#endif // COMPONENTS_COMPONENTS_H
