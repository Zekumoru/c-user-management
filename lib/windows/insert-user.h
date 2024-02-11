#ifndef INSERT_USER_WINDOW_H
#define INSERT_USER_WINDOW_H

#include "../components.h"

typedef struct InsertUserWindow
{
  WindowComponent *component;
  void (*destroy)(Window *window);

  // UI Properties
  TextInputComponent *nameInput;
  TextInputComponent *surnameInput;
  DoubleInputComponent *wageInput;
} InsertUserWindow;

InsertUserWindow *createInsertUserWindow();

#endif // INSERT_USER_WINDOW_H
