#include "lib/components.h"
#include "lib/windows.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

void init()
{
  initscr();
  noecho();
  cbreak();
  curs_set(0);
}

char *logic(WindowManager *wm, int charInput)
{
  return NULL;
}

void handleEvent(char *eventName, FILE *fp)
{
  if (eventName == NULL)
  {
    return;
  }
}

void render(WindowManager *wm)
{
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

int main()
{
  init();

  // Define variables
  WindowManager *wm = createWindowManager();
  pushWindow(wm, createMainMenuWindow());
  char *eventName = NULL;
  int charInput = 0;
  FILE *fp = NULL;

  // Main program loop
  while (true)
  {
    // Logic
    eventName = logic(wm, charInput);
    if (eventName != NULL && strcmp(eventName, "exit") == 0)
    {
      break;
    }

    // Events
    handleEvent(eventName, fp);

    // Render
    render(wm);

    // Input
    charInput = input();

    // Cleanup
    if (eventName != NULL)
    {
      free(eventName);
    }
  }

  // Cleanup and exit
  free(eventName);
  cleanup();
  return 0;
}
