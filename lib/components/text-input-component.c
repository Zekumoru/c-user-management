#include "components.h"
#include "../utils.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

char *logicTextInputComponent(Component *_tic, int charInput)
{
  TextInputComponent *tic = (TextInputComponent *)_tic;

  // if it ain't focused then return
  if (!tic->proto->hasFocus)
  {
    return NULL;
  }

  // handle moving through the string
  if (charInput == KEY_LEFT && tic->curpos > 0)
  {
    tic->curpos--;
  }

  if (charInput == KEY_RIGHT && tic->curpos < strlen(tic->value))
  {
    tic->curpos++;
  }

  // handle backspace
  if (charInput == KEY_BACKSPACE || charInput == '\b')
  {
    size_t currentSize = strlen(tic->value) + 1; // +1 because of the '\0' char
    // remove char from end of string if the cursor is there
    // otherwise remove the char in the string specified by the cursor
    // though if the cursor is at the start of string, don't remove
    if (tic->curpos == 0)
    {
      return NULL;
    }
    else
    {
      // copy over while removing the character specified by the current user
      char *prevValue = strdup(tic->value);
      // -1 because the cursor is after the char to remove
      size_t posToRemove = tic->curpos - 1;
      for (size_t i = 0, j = 0; i < currentSize - 1; i++, j++)
      {
        if (posToRemove == i && posToRemove == j)
        {
          j--;
        }
        else
        {
          tic->value[j] = prevValue[i];
        }
      }
      free(prevValue);
    }
    // line below handles both backspacing from end of string or in the middle
    tic->value[currentSize - 2] = '\0';
    tic->curpos--;
  }

  // if char input is not a valid printable character
  if (charInput < 32 || charInput > 255)
  {
    return NULL;
  }

  // +2 because of the '\0' char and the new char to insert
  size_t currentSize = strlen(tic->value) + 2;
  tic->value = dalloc(tic->value, sizeof(char), currentSize, tic->valueAllocSize);

  // append char to end of string if the cursor is there
  // otherwise insert the char in the string specified by the cursor
  if (tic->curpos == currentSize - 2)
  {
    tic->value[currentSize - 2] = (char)charInput;
  }
  else
  {
    char *prevValue = strdup(tic->value);
    for (size_t i = 0, j = 0; i < currentSize - 1; i++, j++)
    {
      if (tic->curpos == i && tic->curpos == j)
      {
        tic->value[j] = (char)charInput;
        i--;
      }
      else
      {
        tic->value[j] = prevValue[i];
      }
    }
    free(prevValue);
  }
  tic->value[currentSize - 1] = '\0';
  tic->curpos++;

  return strdup("key-entered");
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
  tic->valueAllocSize = strlen(value);
  if (tic->valueAllocSize == 0)
  {
    tic->valueAllocSize = 1;
  }
  return tic;
}
