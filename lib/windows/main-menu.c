#include "../windows.h"
#include "../components.h"
#include <string.h>

Window *createMainMenuWindow()
{
  Window *win = createWindow();
  addComponent(win->cm, createHeaderComponent("Main Menu"));
  MenuItemComponent *mic = createMenuItemComponent("Insert user", "open-insert-user-window");
  mic->proto->hasFocus = true;
  win->cm->indexFocusedComponent = 1;
  addComponent(win->cm, mic);
  addComponent(win->cm, createTextInputComponent("Label", "", "label-test"));
  addComponent(win->cm, createMenuItemComponent("Delete user", "open-delete-user-window"));
  addComponent(win->cm, createMenuItemComponent("Find user", "open-find-user-window"));
  addComponent(win->cm, createMenuItemComponent("Modify user", "open-modify-user-window"));
  addComponent(win->cm, createMenuItemComponent("View all users", "open-view-all-users-window"));
  addComponent(win->cm, createMenuItemComponent("Quit", "exit"));
  return win;
}
