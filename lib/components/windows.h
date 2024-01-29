#ifndef COMPONENTS_WINDOWS_H
#define COMPONENTS_WINDOWS_H

#include "components.h"
#include <stddef.h>

/**
 * \brief A basic window.
 */
typedef struct Window
{
  ComponentManager *cm;
} Window;

Window *createWindow();
void destroyWindow(Window *win);

/**
 * \brief Manages a stack of windows.
 */
typedef struct WindowManager
{
  Window *current;
  Window **windows;
  size_t size;
  size_t allocSize;
} WindowManager;

WindowManager *createWindowManager();

void pushWindow(WindowManager *wm, Window *win);
void popWindow(WindowManager *wm);

#endif // COMPONENTS_WINDOWS_H
