#ifndef INPUT_COMPONENT_H
#define INPUT_COMPONENT_H

#include "../components.h"

#include <stddef.h>
#include <stdbool.h>

typedef struct InputComponentPrototype
{
  char *label;
  char *placeholder;
  char *input;
  size_t allocSize;
  size_t curpos;
  bool (*customValidator)(char *input, int charInput);
  char *(*logic)(struct InputComponentPrototype *icp, ComponentPrototype *proto, int charInput, bool (*validateFn)(char *input, int charInput));
  void (*render)(struct InputComponentPrototype *icp, ComponentPrototype *proto);
} InputComponentPrototype;

InputComponentPrototype *createInputComponentPrototype(char *label, char *placeholder, char *input, bool (*customValidator)(char *input, int charInput));
void destroyInputComponentPrototype(InputComponentPrototype *icp);

#endif // INPUT_COMPONENT_H
