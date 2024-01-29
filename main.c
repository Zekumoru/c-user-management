#include "lib/components.h"
#include "lib/windows.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

void init();
char *logic(WindowManager *wm, int charInput);
void handleEvent(char *eventName, FILE *fp);
void render(WindowManager *wm);
int input();
void cleanup();

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

void init()
{
  initscr();
  noecho();
  cbreak();
  keypad(stdscr, true);
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
  clear();

  ComponentManager *cm = wm->current->cm;
  Component **components = cm->components;

  for (size_t i = 0; i < cm->size; i++)
  {
    StubComponent *component = (StubComponent *)cm->components[i];
    component->proto->render(component);
  }

  refresh();
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
