#include "lib/components.h"
#include "lib/windows.h"
#include "lib/user.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

void init();
Event *logic(WindowManager *wm, int charInput);
void handleEvent(WindowManager *wm, Event *event, FILE *fp, void **data);
void render(WindowManager *wm);
int input();
void cleanup();

int main()
{
  init();

  // Define variables
  WindowManager *wm = createWindowManager();
  pushWindow(wm, createMainMenuWindow());
  Event *event = NULL;
  void **data = malloc(sizeof(void *));
  int charInput = 0;
  FILE *fp = NULL;

  // Main program loop
  while (true)
  {
    // Logic
    event = logic(wm, charInput);
    if (event != NULL && strcmp(event->name, "exit") == 0)
    {
      break;
    }

    // Events
    handleEvent(wm, event, fp, data);

    // Render
    render(wm);

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
  destroyWindowManager(wm);
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

Event *logic(WindowManager *wm, int charInput)
{
  ComponentManager *cm = wm->current->cm;
  int index = cm->indexFocusedComponent;
  StubComponent *focusedComponent = (StubComponent *)cm->components[index];

  Event *event = focusedComponent->proto->logic(focusedComponent, charInput);

  bool found = false;
  switch (charInput)
  {
  // find the previous focusable component
  case KEY_UP:
    for (int i = index - 1; i >= 0; i--)
    {
      if (cm->focusComponent(cm, i))
      {
        found = true;
        break;
      }
    }

    // if not found then start from zero the search
    for (int i = cm->size - 1; i > index && !found; i--)
    {
      if (cm->focusComponent(cm, i))
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
      if (cm->focusComponent(cm, i))
      {
        found = true;
        break;
      }
    }

    // if not found then start from zero the search
    for (int i = 0; i < index && !found; i++)
    {
      if (cm->focusComponent(cm, i))
      {
        break;
      }
    }

    // if still not found, never mind...
    break;
  }

  return event;
}

void handleEvent(WindowManager *wm, Event *event, FILE *fp, void **data)
{
  if (event == NULL)
  {
    return;
  }

  if (strcmp(event->name, "submit-user") == 0)
  {
    InsertUserData *iud = (InsertUserData *)*data;
    User *user = createUser(iud->name, iud->surname, *iud->wage);
    printf("User: %s %s with %.2lf wage!\n", user->name, user->surname, user->wage);
    destroyInsertUserData(iud);
    destroyUser(user);
    *data = NULL;
    popWindow(wm);
  }

  if (strcmp(event->name, "open-insert-user-window") == 0)
  {
    pushWindow(wm, createInsertUserWindow(data));
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
