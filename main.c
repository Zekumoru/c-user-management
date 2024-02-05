#include "lib/components.h"
#include "lib/windows.h"
#include "lib/user.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

void init();
int input();
void cleanup();

int main()
{
  init();

  // Define variables
  WindowManagerComponent *wmc = createWindowManagerComponent();
  wmc->push(wmc, createMainMenuWindowComponent());

  // Main program loop
  int charInput = 0;
  Event *event;
  while (true)
  {
    // Logic
    event = wmc->proto->logic(wmc, charInput);
    if (event != NULL && strcmp(event->name, "exit") == 0)
    {
      break;
    }

    // Render
    clear();
    wmc->proto->render(wmc);
    refresh();

    // Input
    charInput = input();

    // Cleanup
    if (event != NULL)
    {
      event->destroy(event);
      event = NULL;
    }
  }

  // Cleanup and exit
  wmc->proto->destroy(wmc);
  if (event != NULL)
  {
    event->destroy(event);
  }
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

int input()
{
  return getch();
}

void cleanup()
{
  standend();
  endwin();
}
