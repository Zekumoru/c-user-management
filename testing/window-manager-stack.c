#include "../lib/components.h"
#include "../lib/windows.h"

int main()
{
  init();

  WindowManagerComponent *wmc = createWindowManagerComponent();
  wmc->push(wmc, createMainMenuWindowComponent());
  wmc->push(wmc, createMainMenuWindowComponent());
  wmc->push(wmc, createMainMenuWindowComponent());
  wmc->push(wmc, createMainMenuWindowComponent());
  wmc->push(wmc, createMainMenuWindowComponent());
  wmc->proto->destroy(wmc);
  cleanup();
  return 0;
}
