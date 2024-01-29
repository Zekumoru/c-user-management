#include "components.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

char *logicMenuItemComponent(Component *_mic, int charInput)
{
  MenuItemComponent *mic = (MenuItemComponent *)_mic;

  if (charInput == KEY_ENTER || charInput == ' ' || charInput == '\n' || charInput == '\r')
  {
    return strdup(mic->proto->eventName);
  }

  return NULL;
}

void renderMenuItemComponent(Component *_mic)
{
  MenuItemComponent *mic = (MenuItemComponent *)_mic;

  if (mic->proto->hasFocus)
  {
    attron(A_STANDOUT);
    printw("->");
  }
  else
  {
    printw("  ");
  }

  printw("%s\n", mic->text);

  if (mic->proto->hasFocus)
  {
    attroff(A_STANDOUT);
  }
}

void destroyMenuItemComponent(Component *_mic)
{
  MenuItemComponent *mic = (MenuItemComponent *)_mic;
  destroyComponentPrototype(mic->proto);
  free(mic->text);
  free(mic);
}

MenuItemComponent *createMenuItemComponent(char text[], char eventName[])
{
  MenuItemComponent *mic = malloc(sizeof(MenuItemComponent));
  mic->proto = createComponentPrototype();
  mic->proto->type = strdup("MenuItemComponent");
  mic->proto->eventName = strdup(eventName);
  mic->proto->focusable = true;
  mic->proto->hasFocus = false;
  mic->proto->logic = logicMenuItemComponent;
  mic->proto->render = renderMenuItemComponent;
  mic->proto->destroy = destroyMenuItemComponent;
  mic->text = strdup(text);
  return mic;
}
