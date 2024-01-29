#include "components.h"
#include <stdlib.h>

ComponentPrototype *createComponentPrototype()
{
  ComponentPrototype *proto = malloc(sizeof(ComponentPrototype));
  proto->type = NULL;
  proto->eventName = NULL;
  proto->focusable = false;
  proto->hasFocus = false;
  proto->arrowsSuppressed = false;
  proto->logic = NULL;
  proto->render = NULL;
  proto->destroy = NULL;
  return proto;
}

void destroyComponentPrototype(ComponentPrototype *proto)
{
  if (proto->eventName != NULL)
  {
    free(proto->eventName);
  }

  free(proto->type);
  free(proto);
}