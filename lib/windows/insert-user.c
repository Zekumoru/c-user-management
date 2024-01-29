#include "../windows.h"

Window *createInsertUserWindow()
{
  Window *win = createWindow();
  addComponent(win->cm, createHeaderComponent("Insert user"));
  TextInputComponent *tic = createTextInputComponent("Name", "", "name-input");
  tic->proto->hasFocus = true;
  win->cm->indexFocusedComponent = 1;
  addComponent(win->cm, tic);
  addComponent(win->cm, createTextInputComponent("Surname", "", "surname-input"));
  addComponent(win->cm, createDoubleInputComponent("Wage", 0, "wage-input"));
  addComponent(win->cm, createMenuItemComponent("Submit", "submit-user"));
  return win;
}
