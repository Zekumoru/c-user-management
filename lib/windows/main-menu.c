#include "../windows.h"
#include "../components.h"
#include <string.h>

Window *createMainMenuWindow()
{
  Window *win = createWindow();
  addComponent(win->cm, createHeaderComponent("Main Menu"));
  return win;
}
