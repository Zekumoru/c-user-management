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
  bool arrowsSuppressed;
  // set cursor to these coordinates after all components have rendered
  int setcurX;
  int setcurY;
  Event *(*logic)(Component *, int);
  void (*render)(Component *);
  void (*destroyProto)(struct ComponentPrototype *);
  void (*destroy)(Component *);
} ComponentPrototype;

/**
 * \brief Creates a new component prototype.
 * \return A component prototype.
 */
ComponentPrototype *createComponentPrototype();

#endif //  COMPONENT_PROTOTYPE_H
