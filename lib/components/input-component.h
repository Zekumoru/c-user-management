#ifndef INPUT_COMPONENT_H
#define INPUT_COMPONENT_H

#include "../components.h"

#include <stddef.h>
#include <stdbool.h>

typedef struct InputComponentPrototype
{
  char *label;
  char *input;
  size_t allocSize;
  size_t curpos;
  char *(*logic)(struct InputComponentPrototype *icp, ComponentPrototype *proto, int charInput, bool (*validateFn)(char *input, int charInput));
  void (*render)(struct InputComponentPrototype *icp, ComponentPrototype *proto);
} InputComponentPrototype;

InputComponentPrototype *createInputComponentPrototype(char *label, char *input);
void destroyInputComponentPrototype(InputComponentPrototype *icp);

#endif // INPUT_COMPONENT_H
