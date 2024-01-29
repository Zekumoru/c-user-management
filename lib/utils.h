#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>
#define dalloc(memory, elementSize, currentSize, allocSize) _dalloc(memory, elementSize, currentSize, &allocSize);

void *_dalloc(void *memory, size_t elementSize, size_t currentSize, size_t *allocSize);

#endif // UTILS_H
