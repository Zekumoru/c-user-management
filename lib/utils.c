#include "utils.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>

void *_dalloc(void *_memory, size_t elementSize, size_t currentSize, size_t *allocSize)
{
  void *memory = _memory;

  // dynamically allocate by O(log n)
  while (currentSize >= *allocSize)
  {
    if (*allocSize == 0)
    {
      *allocSize = 1;
    }
    else
    {
      (*allocSize) *= 2;
    }

    memory = realloc(memory, elementSize * (*allocSize));
  }

  return memory;
}

double toDouble(const char *string)
{
  double num = 0.0;   // first, set the number to 0
  int pos = 0;        // index pointer for the string
  bool isNeg = false; // will be used if the number must be negative

  // will be used to denote that we have finished parsing the whole number
  // part of the string and must parse the decimal part now
  // Example: 123.45 where 123 is the whole number part and 45 is the decimal
  //          part
  // is it also used to prevent inputs with double dots such as 12.3.4 or 1..3
  bool dotFound = false;

  // ignore leading spaces
  for (int i = 0; isspace(string[i]); i++, pos++)
    ;

  // check if the first character found is a minus sign so we know
  // this number should be negated later
  isNeg = string[pos] == '-';
  if (isNeg)
    pos++;

  // convert the string to number while we know the character in the string
  // is a digit or a dot
  // decPlace is a counter to know where we are in the decimal part
  for (int decPlace = 1; isdigit(string[pos]) || string[pos] == '.'; pos++)
  {
    if (string[pos] == '.')
    {
      // already found dot earlier so break out of loop
      if (dotFound)
        break;

      // otherwise this is the first time we encountered a dot
      // so continue the loop and now parse the decimal part
      dotFound = true;
      continue;
    }

    // convert the current character to int
    int digit = string[pos] - '0';

    if (!dotFound)
    {
      // parse whole numbers part

      num *= 10;    // move the number to the left
      num += digit; // then add the current digit
    }
    else
    {
      // parse decimal numbers part

      // digit / (10^decPlace) means to get the placement of the current
      // digit in the decimal part
      // Example: 123.45 where 5 is in the second place hence it'd be
      //          5 / (10^2) = 5 / 100 = 0.05
      double dec = digit / pow(10, decPlace);

      decPlace++; // move to the next decimal part
      num += dec; // add that decimal part to the number
    }
  }

  // if earlier we know this number is negative, negate it
  // we couldn't negate earlier because of the fact that the number was 0
  // and anything times to 0 is 0 so we negate here
  if (isNeg)
    num *= -1;

  return num;
}
