#include "components.h"
#include <stdlib.h>

ComponentPrototype *createComponentPrototype()
{
  ComponentPrototype *proto = malloc(sizeof(ComponentPrototype));
  proto->type = NULL;
  proto->focusable = false;
  proto->logic = NULL;
  proto->delete = NULL;
  return proto;
}

void destroyComponentPrototype(ComponentPrototype *proto)
{
  free(proto->type);
  free(proto);
}