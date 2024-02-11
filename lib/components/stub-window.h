#ifndef STUB_WINDOW_H
#define STUB_WINDOW_H

#include "components.h"

/**
 * \brief A struct to denote an unknown component.
 */
typedef struct StubWindow
{
  WindowComponent *component;
  void (*destroy)(Window *window);
} StubWindow;

#endif // STUB_WINDOW_H
