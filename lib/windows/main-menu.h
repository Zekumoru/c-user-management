#ifndef MAIN_MENU_WINDOW_H
#define MAIN_MENU_WINDOW_H

#include "../components.h"

typedef struct MainMenuWindow
{
  WindowComponent *component;
  void (*destroy)(Window *window);

  // UI Properties
  HeaderComponent *titleHeader;
  MenuItemComponent *insertUserMenuItem;
  MenuItemComponent *deleteUserMenuItem;
  MenuItemComponent *findUserMenuItem;
  MenuItemComponent *modifyUserMenuItem;
  MenuItemComponent *viewAllUsersMenuItem;
  MenuItemComponent *quitMenuItem;
} MainMenuWindow;

MainMenuWindow *createMainMenuWindowComponent();

#endif // MAIN_MENU_WINDOW_H
