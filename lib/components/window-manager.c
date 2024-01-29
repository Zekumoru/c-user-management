#include "../components.h"
#include "../utils.h"
#include <stdlib.h>

WindowManager *createWindowManager()
{
  WindowManager *wm = malloc(sizeof(WindowManager));
  size_t size = 0;
  wm->size = size;
  wm->allocSize = size;
  wm->windows = malloc(size);
  return wm;
}

void pushWindow(WindowManager *wm, Window *win)
{
  wm->windows = dalloc(wm->windows, sizeof(Window), wm->size, wm->allocSize);
  wm->current = win;
  wm->windows[wm->size - 1] = win;
}

void popWindow(WindowManager *wm)
{
  destroyWindow(wm->current);
  wm->windows[wm->size - 1] = NULL;
  wm->size--;
  wm->current = wm->windows[wm->size - 1];
}
