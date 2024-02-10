#include "../windows.h"
#include "../components.h"
#include <string.h>

Event *handleEventMainMenuWindow(Event *event)
{
  return event;
}

WindowComponent *createMainMenuWindowComponent()
{
  WindowComponent *win = createWindowComponent();
  win->cm->addComponent(win->cm, createHeaderComponent("Main Menu"));
  MenuItemComponent *mic = createMenuItemComponent("Insert user", "open-insert-user-window");
  mic->proto->hasFocus = true;
  win->cm->indexFocusedComponent = 1;
  win->cm->addComponent(win->cm, mic);
  win->cm->addComponent(win->cm, createMenuItemComponent("Delete user", "open-delete-user-window"));
  win->cm->addComponent(win->cm, createMenuItemComponent("Find user", "open-find-user-window"));
  win->cm->addComponent(win->cm, createMenuItemComponent("Modify user", "open-modify-user-window"));
  win->cm->addComponent(win->cm, createMenuItemComponent("View all users", "open-view-all-users-window"));
  MenuItemComponent *exitMIC = createMenuItemComponent("Quit", "exit");
  exitMIC->proto->id = strdup("exit-menu-item");
  win->cm->addComponent(win->cm, exitMIC);
  win->handleEvent = handleEventMainMenuWindow;
  return win;
}
