#include "../lib/components.h"
#include "../lib/vrender.h"
#include <ncurses.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int main()
{
  init();

  WindowComponent *win = createWindowComponent(NULL);
  ComponentManager *cm = win->cm;

  cm->addComponent(cm, createHeaderComponent("ScrollableComponent\n"));

  for (int i = 0; i < 20; i++)
  {
    char line[128];
    sprintf(line, "Item: %d", i + 1);
    cm->addComponent(cm, createHeaderComponent(line));
  }

  ScrollableComponent *sc = createScrollableComponent(win);
  run(sc);

  cleanup();
  return 0;
}
