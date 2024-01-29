#include "../components.h"
#include <stdlib.h>

Window *createWindow()
{
  Window *win = malloc(sizeof(Window));
  win->cm = createComponentManager();
  return win;
}

void destroyWindow(Window *win)
{
  destroyComponentManager(win->cm);
  free(win);
}
