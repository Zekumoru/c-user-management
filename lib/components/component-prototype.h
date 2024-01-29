#ifndef COMPONENT_PROTOTYPE_H
#define COMPONENT_PROTOTYPE_H

#include "components.h"
#include <stdbool.h>

/**
 * \brief A struct which all components "inherits" from.
 */
typedef struct ComponentPrototype
{
  char *type;
  bool focusable;
  bool hasFocus;
  void (*logic)(Component *, int);
  void (*render)(Component *);
  void (*destroy)(Component *);
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

#endif //  COMPONENT_PROTOTYPE_H
