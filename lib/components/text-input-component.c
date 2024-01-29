#include "components.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

char *logicTextInputComponent(Component *_tic, int charInput)
{
  TextInputComponent *tic = (TextInputComponent *)_tic;
  return NULL;
}

void renderTextInputComponent(Component *_tic)
{
  TextInputComponent *tic = (TextInputComponent *)_tic;
  printw("%s: ", tic->label);

  // print value char by char
  size_t valueLength = strlen(tic->value);
  for (size_t i = 0; i < valueLength; i++)
  {
    if (tic->curpos == i)
    {
      getyx(stdscr, tic->proto->setcurY, tic->proto->setcurX);
    }
    addch(tic->value[i]);
  }

  // set cursor to end of value string if it is supposed to be there
  if (tic->curpos == valueLength)
  {
    getyx(stdscr, tic->proto->setcurY, tic->proto->setcurX);
  }

  addch('\n');
}

void destroyTextInputComponent(Component *_tic)
{
  TextInputComponent *tic = (TextInputComponent *)_tic;
  destroyComponentPrototype(tic->proto);
  free(tic->label);
  free(tic->value);
  free(tic);
}

TextInputComponent *createTextInputComponent(char label[], char value[], char eventName[])
{
  TextInputComponent *tic = malloc(sizeof(TextInputComponent));
  tic->proto = createComponentPrototype();
  tic->proto->type = strdup("TextInputComponent");
  tic->proto->eventName = strdup(eventName);
  tic->proto->focusable = true;
  tic->proto->logic = logicTextInputComponent;
  tic->proto->render = renderTextInputComponent;
  tic->proto->destroy = destroyTextInputComponent;
  tic->label = strdup(label);
  tic->value = strdup(value);
  tic->curpos = strlen(value);
  return tic;
}
