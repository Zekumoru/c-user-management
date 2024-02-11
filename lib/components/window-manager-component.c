#include "window-manager-component.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

WindowNode *createWindowNode(Window *win)
{
  WindowNode *wn = malloc(sizeof(WindowNode));
  wn->win = win;
  wn->next = NULL;
  wn->prev = NULL;
  return wn;
}

Window *peek_WMC(WindowManagerComponent *wmc)
{
  // if there are no windows in the stack, return
  if (wmc->size == 0)
    return NULL;

  // get the window on the top of stack
  return wmc->tail->win;
}

Event *logic_WMC(Component *__wmc, int charInput)
{
  WindowManagerComponent *wmc = (WindowManagerComponent *)__wmc;

  // get the window on the top of stack, return if NULL
  StubWindow *current = (StubWindow *)wmc->peek(wmc);
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

    StubWindow *currentWinNow = wmc->peek(wmc);

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
  StubWindow *current = (StubWindow *)wmc->peek(wmc);
  if (current == NULL)
    return;

  current->component->proto->render(current->component);
}

void destroy_WMC(Component *__wmc)
{
  WindowManagerComponent *wmc = (WindowManagerComponent *)__wmc;
  for (size_t i = 0; i < wmc->size; i++)
  {
    StubWindow *window = (StubWindow *)wmc->pop(wmc);
    window->destroy(window);
  }
  wmc->proto->destroyProto(wmc->proto);
  free(wmc);
}

void push_WMC(WindowManagerComponent *wmc, Window *win)
{
  if (wmc->size == 0)
  {
    // set head and tail both to win
    WindowNode *node = createWindowNode(win);
    wmc->head = node;
    wmc->tail = node;
    wmc->size++;
    return;
  }

  if (wmc->size == 1)
  {
    // set head's next to win and leave
    WindowNode *node = createWindowNode(win);
    node->prev = wmc->head;
    wmc->head->next = node;
    wmc->tail = node;
    wmc->size++;
    return;
  }

  // with size > 2
  WindowNode *newNode = createWindowNode(win);
  WindowNode *current = wmc->head;
  while (current->next != NULL)
    current = current->next;
  current->next = newNode;
  newNode->prev = current;
  wmc->tail = newNode;
  wmc->size++;
}

Window *pop_WMC(WindowManagerComponent *wmc)
{
  if (wmc->size == 0)
    return NULL;

  WindowNode *poppedNode = wmc->tail;

  if (wmc->size == 1)
  {
    wmc->head = NULL;
    wmc->tail = NULL;
  }
  else if (wmc->size == 2)
  {
    wmc->head->next = NULL;
    wmc->tail = wmc->head;
  }
  else
  {
    wmc->tail = poppedNode->prev;
    wmc->tail->next = NULL;
  }

  wmc->size--;

  // returned popped window
  Window *popped = poppedNode->win;
  free(poppedNode);
  return popped;
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
  wmc->head = NULL;
  wmc->tail = NULL;
  wmc->size = 0;
  wmc->push = push_WMC;
  wmc->pop = pop_WMC;
  wmc->peek = peek_WMC;
  return wmc;
}
