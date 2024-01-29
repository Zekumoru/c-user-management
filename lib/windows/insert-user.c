#include "insert-user.h"
#include <stdlib.h>

InsertUserData *createInsertUserData()
{
  InsertUserData *iud = malloc(sizeof(InsertUserData));
  iud->name = NULL;
  iud->surname = NULL;
  iud->wage = NULL;
  return iud;
}

void destroyInsertUserData(InsertUserData *iud)
{
  free(iud->name);
  free(iud->surname);
  free(iud->wage);
  free(iud);
}

Window *createInsertUserWindow(void **data)
{
  Window *win = createWindow();
  InsertUserData *iud = createInsertUserData();
  addComponent(win->cm, createHeaderComponent("Insert user"));
  TextInputComponent *tic = createTextInputComponent("Name", "", "name-input", &iud->name);
  tic->proto->hasFocus = true;
  win->cm->indexFocusedComponent = 1;
  addComponent(win->cm, tic);
  addComponent(win->cm, createTextInputComponent("Surname", "", "surname-input", &iud->surname));
  addComponent(win->cm, createDoubleInputComponent("Wage", 0, "wage-input", &iud->wage));
  addComponent(win->cm, createMenuItemComponent("Submit", "submit-user"));
  *data = (void *)iud;
  return win;
}
