#include "components.h"
#include "../utils.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

char *logicDoubleInputComponent(Component *_dic, int charInput)
{
  DoubleInputComponent *dic = (DoubleInputComponent *)_dic;

  // if it ain't focused then return
  if (!dic->proto->hasFocus)
  {
    return NULL;
  }

  // handle enter
  if (charInput == KEY_ENTER || charInput == '\n' || charInput == '\r')
  {
    return dic->proto->eventName;
  }

  // handle moving through the string
  if (charInput == KEY_LEFT && dic->curpos > 0)
  {
    dic->curpos--;
  }

  if (charInput == KEY_RIGHT && dic->curpos < strlen(dic->valueString))
  {
    dic->curpos++;
  }

  // handle backspace
  if (charInput == KEY_BACKSPACE || charInput == '\b')
  {
    size_t currentSize = strlen(dic->valueString) + 1; // +1 because of the '\0' char
    // remove char from end of string if the cursor is there
    // otherwise remove the char in the string specified by the cursor
    // though if the cursor is at the start of string, don't remove
    if (dic->curpos == 0)
    {
      return NULL;
    }
    else
    {
      // copy over while removing the character specified by the current user
      char *prevValue = strdup(dic->valueString);
      // -1 because the cursor is after the char to remove
      size_t posToRemove = dic->curpos - 1;
      for (size_t i = 0, j = 0; i < currentSize - 1; i++, j++)
      {
        if (posToRemove == i && posToRemove == j)
        {
          j--;
        }
        else
        {
          dic->valueString[j] = prevValue[i];
        }
      }
      free(prevValue);
    }
    // line below handles both backspacing from end of string or in the middle
    dic->valueString[currentSize - 2] = '\0';
    dic->curpos--;
  }

  // if char input is not a valid digit
  if ((charInput < '0' || charInput > '9') && charInput != '.')
  {
    return NULL;
  }

  // if there's already a dot then ignore
  if (strchr(dic->valueString, '.') && charInput == '.')
  {
    return NULL;
  }

  // +2 because of the '\0' char and the new char to insert
  size_t currentSize = strlen(dic->valueString) + 2;
  dic->valueString = dalloc(dic->valueString, sizeof(char), currentSize, dic->valueAllocSize);

  // append char to end of string if the cursor is there
  // otherwise insert the char in the string specified by the cursor
  if (dic->curpos == currentSize - 2)
  {
    dic->valueString[currentSize - 2] = (char)charInput;
  }
  else
  {
    char *prevValue = strdup(dic->valueString);
    for (size_t i = 0, j = 0; i < currentSize - 1; i++, j++)
    {
      if (dic->curpos == i && dic->curpos == j)
      {
        dic->valueString[j] = (char)charInput;
        i--;
      }
      else
      {
        dic->valueString[j] = prevValue[i];
      }
    }
    free(prevValue);
  }
  dic->valueString[currentSize - 1] = '\0';
  dic->curpos++;

  dic->value = toDouble(dic->valueString);

  return strdup("key-entered");
}

void renderDoubleInputComponent(Component *_dic)
{
  DoubleInputComponent *dic = (DoubleInputComponent *)_dic;
  printw("%s: ", dic->label);

  // print value char by char
  size_t valueLength = strlen(dic->valueString);
  for (size_t i = 0; i < valueLength; i++)
  {
    if (dic->curpos == i)
    {
      getyx(stdscr, dic->proto->setcurY, dic->proto->setcurX);
    }
    addch(dic->valueString[i]);
  }

  // set cursor to end of value string if it is supposed to be there
  if (dic->curpos == valueLength)
  {
    getyx(stdscr, dic->proto->setcurY, dic->proto->setcurX);
  }

  addch('\n');
}

void destroyDoubleInputComponent(Component *_dic)
{
  DoubleInputComponent *dic = (DoubleInputComponent *)_dic;
  destroyComponentPrototype(dic->proto);
  free(dic->label);
  free(dic->valueString);
  free(dic);
}

DoubleInputComponent *createDoubleInputComponent(char label[], double value, char eventName[], double **outValue)
{
  DoubleInputComponent *dic = malloc(sizeof(DoubleInputComponent));
  dic->proto = createComponentPrototype();
  dic->proto->type = strdup("DoubleInputComponent");
  dic->proto->eventName = strdup(eventName);
  dic->proto->focusable = true;
  dic->proto->logic = logicDoubleInputComponent;
  dic->proto->render = renderDoubleInputComponent;
  dic->proto->destroy = destroyDoubleInputComponent;
  dic->label = strdup(label);
  *outValue = &dic->value;

  char valueString[100];
  sprintf(valueString, "%.2lf", value);
  dic->valueString = strdup(valueString);
  dic->curpos = strlen(valueString);
  dic->valueAllocSize = strlen(valueString);
  if (dic->valueAllocSize == 0)
  {
    dic->valueAllocSize = 1;
  }
  return dic;
}
