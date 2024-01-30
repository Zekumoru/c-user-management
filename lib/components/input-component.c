#include "input-component.h"
#include "../utils.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

char *logicInputComponentPrototype(InputComponentPrototype *icp, ComponentPrototype *proto, int charInput, bool (*validateFn)(char *input, int charInput))
{
  // if it ain't focused then return
  if (!proto->hasFocus)
  {
    return NULL;
  }

  // handle enter
  if (charInput == KEY_ENTER || charInput == '\n' || charInput == '\r')
  {
    return proto->eventName;
  }

  // handle moving through the string
  if (charInput == KEY_LEFT && icp->curpos > 0)
  {
    icp->curpos--;
  }

  if (charInput == KEY_RIGHT && icp->curpos < strlen(icp->input))
  {
    icp->curpos++;
  }

  // handle backspace
  if (charInput == KEY_BACKSPACE || charInput == '\b')
  {
    size_t currentSize = strlen(icp->input) + 1; // +1 because of the '\0' char
    // remove char from end of string if the cursor is there
    // otherwise remove the char in the string specified by the cursor
    // though if the cursor is at the start of string, don't remove
    if (icp->curpos == 0)
    {
      return NULL;
    }
    else
    {
      // copy over while removing the character specified by the current user
      char *prevInput = strdup(icp->input);
      // -1 because the cursor is after the char to remove
      size_t posToRemove = icp->curpos - 1;
      for (size_t i = 0, j = 0; i < currentSize - 1; i++, j++)
      {
        if (posToRemove == i && posToRemove == j)
        {
          j--;
        }
        else
        {
          icp->input[j] = prevInput[i];
        }
      }
      free(prevInput);
    }
    // line below handles both backspacing from end of string or in the middle
    icp->input[currentSize - 2] = '\0';
    icp->curpos--;
  }

  // Run custom validators
  if (!validateFn(icp->input, charInput))
  {
    return NULL;
  }

  if (icp->customValidator != NULL && !icp->customValidator(icp->input, charInput))
  {
    return NULL;
  }

  // +2 because of the '\0' char and the new char to insert
  size_t currentSize = strlen(icp->input) + 2;
  icp->input = dalloc(icp->input, sizeof(char), currentSize, icp->allocSize);

  // append char to end of string if the cursor is there
  // otherwise insert the char in the string specified by the cursor
  if (icp->curpos == currentSize - 2)
  {
    icp->input[currentSize - 2] = (char)charInput;
  }
  else
  {
    char *prevInput = strdup(icp->input);
    for (size_t i = 0, j = 0; i < currentSize - 1; i++, j++)
    {
      if (icp->curpos == i && icp->curpos == j)
      {
        icp->input[j] = (char)charInput;
        i--;
      }
      else
      {
        icp->input[j] = prevInput[i];
      }
    }
    free(prevInput);
  }
  icp->input[currentSize - 1] = '\0';
  icp->curpos++;

  return NULL;
}

void renderInputComponentPrototype(InputComponentPrototype *icp, ComponentPrototype *proto)
{
  printw("%s: ", icp->label);
  size_t inputLength = strlen(icp->input);

  // print placeholder if input is empty
  if (inputLength == 0)
  {
    getyx(stdscr, proto->setcurY, proto->setcurX);
    printw("(%s)\n", icp->placeholder);
    return;
  }

  // print value char by char
  for (size_t i = 0; i < inputLength; i++)
  {
    if (icp->curpos == i)
    {
      getyx(stdscr, proto->setcurY, proto->setcurX);
    }
    addch(icp->input[i]);
  }

  // set cursor to end of value string if it is supposed to be there
  if (icp->curpos == inputLength)
  {
    getyx(stdscr, proto->setcurY, proto->setcurX);
  }

  addch('\n');
}

InputComponentPrototype *createInputComponentPrototype(char *label, char *placeholder, char *input, bool (*customValidator)(char *input, int charInput))
{
  InputComponentPrototype *icp = malloc(sizeof(InputComponentPrototype));
  icp->label = strdup(label);
  icp->placeholder = strdup(placeholder);
  icp->input = strdup(input);
  icp->curpos = strlen(input);
  icp->allocSize = strlen(input);
  if (icp->allocSize == 0)
  {
    icp->allocSize = 1;
  }
  icp->logic = logicInputComponentPrototype;
  icp->render = renderInputComponentPrototype;
  icp->customValidator = customValidator;
  return icp;
}

void destroyInputComponentPrototype(InputComponentPrototype *icp)
{
  free(icp->label);
  free(icp->placeholder);
  free(icp->input);
  free(icp);
}
