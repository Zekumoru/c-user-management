#include "window-manager-component.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

Component *getTopComponent_WMC(WindowManagerComponent *wmc)
{
  ComponentManager *cm = wmc->cm;

  // if there are no components in the stack, return
  if (cm->size == 0)
    return NULL;

  // get the component on the top of stack
  return cm->components[cm->size - 1];
}

Event *logic_WMC(Component *__wmc, int charInput)
{
  WindowManagerComponent *wmc = (WindowManagerComponent *)__wmc;

  // get the component on the top of stack, return if NULL
  StubComponent *current = (StubComponent *)getTopComponent_WMC(wmc);
  if (current == NULL)
    return NULL;

  return current->proto->logic(current, charInput);
}

void render_WMC(Component *__wmc)
{
  WindowManagerComponent *wmc = (WindowManagerComponent *)__wmc;

  // get the component on the top of stack, return if NULL
  StubComponent *current = (StubComponent *)getTopComponent_WMC(wmc);
  if (current == NULL)
    return;

  current->proto->render(current);
}

void destroy_WMC(Component *__wmc)
{
  WindowManagerComponent *wmc = (WindowManagerComponent *)__wmc;
  wmc->cm->destroy(wmc->cm);
  wmc->proto->destroyProto(wmc->proto);
  free(wmc);
}

void push_WMC(WindowManagerComponent *wmc, Component *component)
{
  wmc->cm->addComponent(wmc->cm, component);
}

void pop_WMC(WindowManagerComponent *wmc)
{
  if (wmc->cm->size == 0)
    return;
  wmc->cm->removeComponent(wmc->cm, wmc->cm->size - 1);
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
