#include "components.h"
#include <stdlib.h>

char *logicComponentPrototype(Component *proto, int charInput) {}
void renderComponentPrototype(Component *proto) {}

void destroyComponentPrototype(Component *__proto)
{
  ComponentPrototype *proto = (ComponentPrototype *)__proto;

  if (proto->eventName != NULL)
  {
    free(proto->eventName);
  }

  free(proto->type);
  free(proto);
}

ComponentPrototype *createComponentPrototype()
{
  ComponentPrototype *proto = malloc(sizeof(ComponentPrototype));
  proto->type = NULL;
  proto->eventName = NULL;
  proto->focusable = false;
  proto->hasFocus = false;
  proto->arrowsSuppressed = false;
  // where to put cursor after rending, negative coordinates mean to ignore
  proto->setcurX = -1;
  proto->setcurY = -1;
  proto->logic = logicComponentPrototype;
  proto->render = renderComponentPrototype;
  proto->destroy = destroyComponentPrototype;
  return proto;
}