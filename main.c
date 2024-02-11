#include "lib/components.h"
#include "lib/windows.h"
#include "lib/user.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

void init();
void run(Component *__component);
int input();
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

void run(Component *__component)
{
  StubComponent *component = (StubComponent *)__component;

  int charInput = 0;
  Event *event;
  while (true)
  {
    // Logic
    event = component->proto->logic(component, charInput);
    if (event != NULL && strcmp(event->name, "exit") == 0)
    {
      break;
    }

    // Render
    clear();
    component->proto->render(component);
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
  component->proto->destroy(component);
  if (event != NULL)
  {
    event->destroy(event);
  }
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
