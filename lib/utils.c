#include "utils.h"
#include <stddef.h>
#include <stdlib.h>

void *_dalloc(void *memory, size_t elementSize, size_t *currentSize, size_t *allocSize)
{
  // dynamically allocate by O(log n)
  if (*currentSize >= *allocSize)
  {
    if (*allocSize == 0)
    {
      *allocSize = 1;
    }
    else
    {
      (*allocSize) *= 2;
    }

    (*currentSize)++;
    return realloc(memory, elementSize * (*allocSize));
  }
}