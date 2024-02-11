#include "main-menu.h"
#include "../windows.h"
#include "../user.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Event *handleEventMainMenuWindow(Window *__mmw, Event *event)
{
  MainMenuWindow *mmw = (MainMenuWindow *)__mmw;
  if (event == NULL)
    return NULL;

  if (strcmp(event->name, "click") == 0)
  {
    MenuItemComponent *mic = (MenuItemComponent *)event->sender;

    if (strcmp(mic->proto->id, "exit-item") == 0)
      return createEvent("exit", mmw->component, NULL);
    if (strcmp(mic->proto->id, "insert-user-item") == 0)
      return createEvent("push", mmw->component, createInsertUserWindow());
  }

  if (strcmp(event->name, "new-user") == 0)
  {
    User *newUser = (User *)event->payload;
    printf("New user: %s %s (Wage: %.2lf)\n", newUser->name, newUser->surname, newUser->wage);
    destroyUser(newUser);
  }

  return event;
}

void destroyMainMenuWindow(Window *__mmw)
{
  MainMenuWindow *mmw = (MainMenuWindow *)__mmw;
  WindowComponent *wc = mmw->component;
  wc->proto->destroy(wc);
  free(mmw);
}

MainMenuWindow *createMainMenuWindowComponent()
{
  MainMenuWindow *mmw = malloc(sizeof(MainMenuWindow));
  WindowComponent *win = createWindowComponent(mmw);
  win->handleEvent = handleEventMainMenuWindow;
  mmw->destroy = destroyMainMenuWindow;
  mmw->component = win;

  // Add UI components
  ComponentManager *cm = win->cm;

  mmw->titleHeader = createHeaderComponent("Main Menu");
  cm->addComponent(cm, mmw->titleHeader);

  mmw->insertUserMenuItem = createMenuItemComponent("Insert user", "insert-user-item");
  // focusing first item is manual for now...
  mmw->insertUserMenuItem->proto->hasFocus = true;
  cm->indexFocusedComponent = 1;
  cm->addComponent(cm, mmw->insertUserMenuItem);

  mmw->deleteUserMenuItem = createMenuItemComponent("Delete user", "delete-user-item");
  cm->addComponent(cm, mmw->deleteUserMenuItem);
  mmw->findUserMenuItem = createMenuItemComponent("Find user", "find-user-item");
  cm->addComponent(cm, mmw->findUserMenuItem);
  mmw->modifyUserMenuItem = createMenuItemComponent("Modify user", "modify-user-item");
  cm->addComponent(cm, mmw->modifyUserMenuItem);
  mmw->viewAllUsersMenuItem = createMenuItemComponent("View all users", "view-all-users-item");
  cm->addComponent(cm, mmw->viewAllUsersMenuItem);

  mmw->quitMenuItem = createMenuItemComponent("Quit", "exit-item");
  cm->addComponent(cm, mmw->quitMenuItem);

  return mmw;
}
