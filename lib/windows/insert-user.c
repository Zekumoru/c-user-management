#include "insert-user.h"
#include <stdlib.h>
#include <ctype.h>

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
  // We don't free the members of this InsertUserData since their values
  // are addresses to the component's values hence it's the component
  // that will free them from memory
  free(iud);
}

bool validateAlphaOnly(char *input, int charInput)
{
  return isalpha(charInput) || charInput == ' ';
}

Window *createInsertUserWindow(void **data)
{
  TextInputComponent *tic;
  Window *win = createWindow();
  InsertUserData *iud = createInsertUserData();
  addComponent(win->cm, createHeaderComponent("Insert user"));

  // Setup name text input component
  tic = createTextInputComponent("Name", "name here", "", "name-input", &iud->name);
  tic->proto->hasFocus = true;
  win->cm->indexFocusedComponent = 1;
  tic->ic_proto->customValidator = validateAlphaOnly;
  addComponent(win->cm, tic);

  // Setup surname text input component
  tic = createTextInputComponent("Surname", "surname here", "", "surname-input", &iud->surname);
  tic->ic_proto->customValidator = validateAlphaOnly;
  addComponent(win->cm, tic);

  addComponent(win->cm, createDoubleInputComponent("Wage", "0.00", 0, "wage-input", &iud->wage));
  addComponent(win->cm, createMenuItemComponent("Submit", "submit-user"));
  *data = (void *)iud;
  return win;
}
