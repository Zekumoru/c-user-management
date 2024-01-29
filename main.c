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

bool focusComponent(ComponentManager *cm, size_t i, bool *found, StubComponent *prevFocusedComponent)
{
  StubComponent *component = (StubComponent *)cm->components[i];
  if (component->proto->focusable)
  {
    *found = true;
    prevFocusedComponent->proto->hasFocus = false;
    cm->indexFocusedComponent = i;
    component->proto->hasFocus = true;
    return true;
  }
  return false;
}

char *logic(WindowManager *wm, int charInput)
{
  ComponentManager *cm = wm->current->cm;
  int index = cm->indexFocusedComponent;
  StubComponent *focusedComponent = (StubComponent *)cm->components[index];
  bool found = false;

  char *eventName = focusedComponent->proto->logic(focusedComponent, charInput);

  switch (charInput)
  {
  // find the previous focusable component
  case KEY_UP:
    for (int i = index - 1; i >= 0; i--)
    {
      if (focusComponent(cm, i, &found, focusedComponent))
      {
        break;
      }
    }

    // if not found then start from zero the search
    for (int i = cm->size - 1; i > index && !found; i--)
    {
      if (focusComponent(cm, i, &found, focusedComponent))
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
      if (focusComponent(cm, i, &found, focusedComponent))
      {
        break;
      }
    }

    // if not found then start from zero the search
    for (int i = 0; i < index && !found; i++)
    {
      if (focusComponent(cm, i, &found, focusedComponent))
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
