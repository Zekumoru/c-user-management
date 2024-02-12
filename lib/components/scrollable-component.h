#ifndef SCROLLABLE_COMPONENT
#define SCROLLABLE_COMPONENT

#include "components.h"
#include <stdbool.h>

typedef struct ScrollableComponent
{
  ComponentPrototype *proto;
  // the component to have scrollability
  Component *component; // TODO: ScrollableComponent sets the proto coords using
                        //       its own proto coords to this component.
  // enable/disable scrollability
  bool horizontalScrolling;
  bool verticalScrolling;
  // current scroll values
  int scrollX;
  int scrollY;
  // max scroll values
  int scrollMaxX;
  int scrollMaxY;
} ScrollableComponent;

ScrollableComponent *createScrollableComponent(Component *componentToScroll);

#endif // SCROLLABLE_COMPONENT
