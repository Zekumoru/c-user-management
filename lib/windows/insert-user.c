#include "../windows.h"
#include "../user.h"

Window *createInsertUserWindow(void **data)
{
  Window *win = createWindow();
  User *user = createUser();
  addComponent(win->cm, createHeaderComponent("Insert user"));
  TextInputComponent *tic = createTextInputComponent("Name", "", "name-input", &user->name);
  tic->proto->hasFocus = true;
  win->cm->indexFocusedComponent = 1;
  addComponent(win->cm, tic);
  addComponent(win->cm, createTextInputComponent("Surname", "", "surname-input", &user->surname));
  addComponent(win->cm, createDoubleInputComponent("Wage", 0, "wage-input", &user->wage));
  addComponent(win->cm, createMenuItemComponent("Submit", "submit-user"));
  *data = (void *)user;
  return win;
}
