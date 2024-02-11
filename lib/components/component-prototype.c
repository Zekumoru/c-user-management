#include "components.h"
#include <stdlib.h>
#include <ncurses.h>

void destroyComponentPrototype(ComponentPrototype *proto)
{
  if (proto->id != NULL)
    free(proto->id);
  if (proto->type != NULL)
    free(proto->type);
  free(proto);
}

ComponentPrototype *createComponentPrototype()
{
  ComponentPrototype *proto = malloc(sizeof(ComponentPrototype));
  proto->id = NULL;
  proto->type = NULL;
  proto->focusable = false;
  proto->hasFocus = false;
  proto->arrowsSuppressed = false;

  // where to put cursor after rending, negative coordinates mean to ignore
  proto->setcurX = -1;
  proto->setcurY = -1;

  proto->screenX = 0;
  proto->screenY = 0;
  proto->renderX = 0;
  proto->renderY = 0;
  getmaxyx(stdscr, proto->screenMaxY, proto->screenMaxX);
  proto->screenMaxX -= proto->screenX;
  proto->screenMaxY -= proto->screenY;

  proto->autoNewline = true;

  proto->destroyProto = destroyComponentPrototype;
  // the methods below must be assigned when making a component
  proto->logic = NULL;
  proto->render = NULL;
  proto->destroy = NULL;
  return proto;
}
