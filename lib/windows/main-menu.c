#include "../windows.h"
#include "../components.h"
#include <string.h>

Window *createMainMenuWindow()
{
  Window *win = createWindow();
  HeaderComponent *hc = createHeaderComponent();
  hc->text = strdup("Main Menu");
  addComponent(win->cm, hc);
  return win;
}
