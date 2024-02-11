#include "lib/components.h"
#include "lib/windows.h"
#include "lib/user.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  init();

  WindowManagerComponent *wmc = createWindowManagerComponent();
  wmc->push(wmc, createMainMenuWindowComponent());
  run(wmc);

  cleanup();
  return 0;
}
