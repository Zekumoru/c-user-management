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
  }

  // Cleanup and exit
  destroyWindowManager(wm);
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
  ComponentManager *cm = wm->current->cm;
  int index = cm->indexFocusedComponent;
  StubComponent *focusedComponent = (StubComponent *)cm->components[index];

  char *eventName = focusedComponent->proto->logic(focusedComponent, charInput);

  bool found = false;
  switch (charInput)
  {
  // find the previous focusable component
  case KEY_UP:
    for (int i = index - 1; i >= 0; i--)
    {
      if (focusComponent(cm, i))
      {
        found = true;
        break;
      }
    }

    // if not found then start from zero the search
    for (int i = cm->size - 1; i > index && !found; i--)
    {
      if (focusComponent(cm, i))
      {
        break;
      }
    }

    // if still not found, never mind...
    break;
  // find the next focusable component
  case 9: // TAB
  case KEY_DOWN:
    for (int i = index + 1; i < cm->size; i++)
    {
      if (focusComponent(cm, i))
      {
        found = true;
        break;
      }
    }

    // if not found then start from zero the search
    for (int i = 0; i < index && !found; i++)
    {
      if (focusComponent(cm, i))
      {
        break;
      }
    }

    // if still not found, never mind...
    break;
  }

  return eventName;
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

  // set cursor position on the screen (or hide it for that matter)
  StubComponent *focusedComponent = (StubComponent *)cm->components[cm->indexFocusedComponent];
  int setcurX = focusedComponent->proto->setcurX;
  int setcurY = focusedComponent->proto->setcurY;
  if (setcurX >= 0 && setcurY >= 0)
  {
    curs_set(1);
    move(setcurY, setcurX);
  }
  else
  {
    curs_set(0);
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
