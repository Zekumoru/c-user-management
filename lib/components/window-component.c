#include "components.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

void focusPreviousComponent(ComponentManager *cm);
void focusNextComponent(ComponentManager *cm);

Event *logicWindowComponent(Component *__wc, int charInput)
{
  WindowComponent *wc = (WindowComponent *)__wc;
  ComponentManager *cm = wc->cm;
  int index = cm->indexFocusedComponent;
  StubComponent *focusedComponent = (StubComponent *)cm->components[index];

  Event *event = focusedComponent->proto->logic(focusedComponent, charInput);

  switch (charInput)
  {
  case KEY_UP:
    focusPreviousComponent(cm);
    break;
  case 9: // TAB
  case KEY_DOWN:
    focusNextComponent(cm);
    break;
  }

  if (wc->handleEvent != NULL)
  {
    return wc->handleEvent(wc->__window, event);
  }

  return NULL;
}

void renderWindowComponent(Component *__wc)
{
  WindowComponent *wc = (WindowComponent *)__wc;
  ComponentManager *cm = wc->cm;
  Component **components = cm->components;

  for (size_t i = 0; i < cm->size; i++)
  {
    StubComponent *component = (StubComponent *)cm->components[i];
    component->proto->render(component);
  }

  // set cursor position on the screen (or hide it for that matter)
  StubComponent *focusedComponent = (StubComponent *)cm->components[cm->indexFocusedComponent];
  int setcurX = focusedComponent->proto->setcurX;
  int setcurY = focusedComponent->proto->setcurY;
  if (setcurX >= 0 && setcurY >= 0)
  {
    curs_set(1);
    move(setcurY, setcurX);
  }
  else
  {
    curs_set(0);
  }
}

void destroyWindowComponent(Component *__wc)
{
  WindowComponent *wc = (WindowComponent *)__wc;
  wc->cm->destroy(wc->cm);
  wc->proto->destroyProto(wc->proto);
  free(wc);
}

WindowComponent *createWindowComponent(Window *window)
{
  WindowComponent *wc = malloc(sizeof(WindowComponent));
  wc->proto = createComponentPrototype();
  wc->proto->type = strdup("WindowComponent");
  wc->proto->focusable = true;
  wc->proto->logic = logicWindowComponent;
  wc->proto->render = renderWindowComponent;
  wc->proto->destroy = destroyWindowComponent;
  wc->cm = createComponentManager();
  wc->__window = window;
  wc->handleEvent = NULL;
  return wc;
}

/**
 * Helper functions
 */

void focusPreviousComponent(ComponentManager *cm)
{
  // find the previous focusable component
  int currentFocusedIndex = cm->indexFocusedComponent;
  bool found = false;

  for (int i = currentFocusedIndex - 1; i >= 0; i--)
  {
    if (cm->focusComponent(cm, i))
    {
      found = true;
      break;
    }
  }

  // if not found then start from zero the search
  for (int i = cm->size - 1; i > currentFocusedIndex && !found; i--)
  {
    if (cm->focusComponent(cm, i))
    {
      break;
    }
  }

  // if still not found, never mind...
  return;
}

void focusNextComponent(ComponentManager *cm)
{
  // find the next focusable component
  int currentFocusedIndex = cm->indexFocusedComponent;
  bool found = false;

  for (int i = currentFocusedIndex + 1; i < cm->size; i++)
  {
    if (cm->focusComponent(cm, i))
    {
      found = true;
      break;
    }
  }

  // if not found then start from zero the search
  for (int i = 0; i < currentFocusedIndex && !found; i++)
  {
    if (cm->focusComponent(cm, i))
    {
      break;
    }
  }

  // if still not found, never mind...
  return;
}
