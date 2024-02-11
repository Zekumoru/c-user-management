#include "insert-user.h"
#include "../user.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

Event *handleEventInsertUserWindow(Window *__iuw, Event *event)
{
  if (event == NULL)
    return NULL;

  InsertUserWindow *iuw = (InsertUserWindow *)__iuw;

  if (strcmp(event->name, "click") == 0)
  {
    MenuItemComponent *mic = (MenuItemComponent *)event->sender;
    if (strcmp(mic->proto->id, "submit-user") == 0)
    {
      User *newUser = createUser(iuw->nameInput->value, iuw->surnameInput->value, iuw->wageInput->value);
      Event *newUserEvent = createEvent("new-user", NULL, newUser);
      return createEvent("pop", NULL, newUserEvent);
    }
  }

  return event;
}

void destroyInsertUserWindow(Window *__iuw)
{
  InsertUserWindow *iuw = (InsertUserWindow *)__iuw;
  WindowComponent *wc = iuw->component;
  wc->proto->destroy(wc);
  free(iuw);
}

bool validateAlphaOnly(char *input, int charInput)
{
  return isalpha(charInput) || charInput == ' ';
}

InsertUserWindow *createInsertUserWindow()
{
  InsertUserWindow *iuw = malloc(sizeof(InsertUserWindow));
  WindowComponent *wc = createWindowComponent(iuw);
  wc->handleEvent = handleEventInsertUserWindow;
  iuw->destroy = destroyInsertUserWindow;
  iuw->component = wc;

  // Add UI components
  ComponentManager *cm = wc->cm;

  cm->addComponent(cm, createHeaderComponent("Insert user"));

  // Setup name text input component
  iuw->nameInput = createTextInputComponent("Name", "name here", "");
  cm->addComponent(cm, iuw->nameInput);

  // Setup surname text input component
  iuw->surnameInput = createTextInputComponent("Surname", "surname here", "");
  iuw->surnameInput->ic_proto->customValidator = validateAlphaOnly;
  cm->addComponent(cm, iuw->surnameInput);

  // Setup wage double input component
  iuw->wageInput = createDoubleInputComponent("Wage", "0.00", 0);
  cm->addComponent(cm, iuw->wageInput);

  cm->addComponent(cm, createMenuItemComponent("Submit", "submit-user"));

  return iuw;
}
