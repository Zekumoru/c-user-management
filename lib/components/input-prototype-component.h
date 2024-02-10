#ifndef INPUT_PROTOTYPE_COMPONENT_H
#define INPUT_PROTOTYPE_COMPONENT_H

#include "../components.h"

#include <stddef.h>
#include <stdbool.h>

/**
 * \brief A struct to a input component prototype containing necessary logic
 *        to handle inputs.
 */
typedef struct InputComponentPrototype
{
  char *label;
  char *placeholder;
  char *input;
  size_t allocSize;
  size_t curpos;
  bool (*customValidator)(char *input, int charInput);
  Event *(*logic)(struct InputComponentPrototype *icp, Component *component, int charInput, bool (*validateFn)(char *input, int charInput));
  void (*render)(struct InputComponentPrototype *icp, Component *component);
  void (*destroy)(struct InputComponentPrototype *icp);
} InputComponentPrototype;

/**
 * \brief Creates a new input component prototype.
 * \return A new input component prototype.
 */
InputComponentPrototype *createInputComponentPrototype(char *label, char *placeholder, char *input, bool (*customValidator)(char *input, int charInput));

#endif // INPUT_PROTOTYPE_COMPONENT_H
