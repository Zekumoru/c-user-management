#include "utils.h"
#include <stddef.h>
#include <stdlib.h>

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