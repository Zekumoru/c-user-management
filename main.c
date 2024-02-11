#include "lib/components.h"
#include "lib/windows.h"
#include "lib/user.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

void init();
void run(Component *__component);
void cleanup();

int main()
{
  init();

  WindowManagerComponent *wmc = createWindowManagerComponent();
  wmc->push(wmc, createMainMenuWindowComponent());
  run(wmc);

  cleanup();
  return 0;
}

void init()
{
  initscr();
  noecho();
  cbreak();
  keypad(stdscr, true);
  curs_set(0);
}

void cleanup()
{
  standend();
  endwin();
}
