#include "window-manager-component.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

Window *getTopWindow_WMC(WindowManagerComponent *wmc)
{
  ComponentManager *cm = wmc->cm;

  // if there are no windows in the stack, return
  if (cm->size == 0)
    return NULL;

  // get the window on the top of stack
  return cm->components[cm->size - 1];
}

Event *logic_WMC(Component *__wmc, int charInput)
{
  WindowManagerComponent *wmc = (WindowManagerComponent *)__wmc;

  // get the window on the top of stack, return if NULL
  StubWindow *current = (StubWindow *)getTopWindow_WMC(wmc);
  if (current == NULL)
    return NULL;

  // handle event
  Event *event = current->component->proto->logic(current->component, charInput);
  if (event == NULL)
    return NULL;

  if (strcmp(event->name, "push") == 0)
  {
    wmc->push(wmc, event->payload);
    return NULL;
  }

  if (strcmp(event->name, "pop") == 0)
  {
    StubWindow *winToDestroy = wmc->pop(wmc);
    winToDestroy->destroy(winToDestroy);

    StubWindow *currentWinNow = getTopWindow_WMC(wmc);

    // if no more windows then pass this "pop" event up
    if (currentWinNow == NULL)
      return event;

    return currentWinNow->component->handleEvent(currentWinNow, (EventPayload *)event->payload);
  }

  return event;
}

void render_WMC(Component *__wmc)
{
  WindowManagerComponent *wmc = (WindowManagerComponent *)__wmc;

  // get the component on the top of stack, return if NULL
  StubWindow *current = (StubWindow *)getTopWindow_WMC(wmc);
  if (current == NULL)
    return;

  current->component->proto->render(current->component);
}

void destroy_WMC(Component *__wmc)
{
  WindowManagerComponent *wmc = (WindowManagerComponent *)__wmc;

  // Free windows from stack
  // Very ugly approach, to be refactored in the future to not use
  // ComponentManager but to implement the stack itself
  ComponentManager *cm = wmc->cm;
  for (size_t i = 0; i < cm->size; i++)
  {
    StubWindow *window = (StubWindow *)cm->components[i];
    window->destroy(window);
  }
  free(cm->components);
  free(cm);

  wmc->proto->destroyProto(wmc->proto);
  free(wmc);
}

void push_WMC(WindowManagerComponent *wmc, Window *__win)
{
  StubWindow *win = (StubWindow *)__win;
  wmc->cm->addComponent(wmc->cm, win);
}

Window *pop_WMC(WindowManagerComponent *wmc)
{
  if (wmc->cm->size == 0)
    return NULL;

  Window *win = getTopWindow_WMC(wmc);
  wmc->cm->size--; // really inefficient, TODO: implement stack logic
  return win;
}

WindowManagerComponent *createWindowManagerComponent()
{
  WindowManagerComponent *wmc = malloc(sizeof(WindowManagerComponent));
  wmc->proto = createComponentPrototype();
  wmc->proto->type = strdup("WindowManagerComponent");
  wmc->proto->focusable = true;
  wmc->proto->logic = logic_WMC;
  wmc->proto->render = render_WMC;
  wmc->proto->destroy = destroy_WMC;
  wmc->cm = createComponentManager();
  wmc->push = push_WMC;
  wmc->pop = pop_WMC;
  return wmc;
}
