#include "scrollable-component.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

void renderScrollableComponent(Component *__sc);

Event *logicScrollableComponent(Component *__sc, int charInput)
{
  ScrollableComponent *sc = (ScrollableComponent *)__sc;

  // calculate max scroll
  renderScrollableComponent(sc);
  StubComponent *component = (StubComponent *)sc->component;
  sc->scrollMaxY = component->proto->renderY;

  switch (charInput)
  {
  case KEY_PPAGE: // page up key
    if (sc->scrollY > 0)
      sc->scrollY--;
    break;
  case KEY_NPAGE: // page down key
    if (sc->scrollY < sc->scrollMaxY)
      sc->scrollY++;
    break;
  }

  return ((StubComponent *)sc->component)->proto->logic(sc->component, charInput);
}

void renderScrollableComponent(Component *__sc)
{
  ScrollableComponent *sc = (ScrollableComponent *)__sc;
  StubComponent *component = (StubComponent *)sc->component;

  component->proto->screenX = sc->scrollX + 2;
  component->proto->screenY = -sc->scrollY;

  int maxY = getmaxy(stdscr) - 1;
  int curY = ((sc->scrollY + 3) / (double)sc->scrollMaxY) * maxY;
  if (curY < 3)
    curY = 3;
  if (curY >= sc->scrollMaxY)
    curY = maxY;
  for (int y = 0; y <= maxY; y++)
    if ((curY - 3) <= y && y <= curY)
      mvaddch(y, 0, '#');
    else
      mvaddch(y, 0, '|');

  component->proto->render(component);
}

void destroyScrollableComponent(Component *__sc)
{
  ScrollableComponent *sc = (ScrollableComponent *)__sc;
  sc->proto->destroyProto(sc->proto);
  free(sc);
}

ScrollableComponent *createScrollableComponent(Component *componentToScroll)
{
  ScrollableComponent *sc = malloc(sizeof(ScrollableComponent));
  sc->proto = createComponentPrototype();
  sc->proto->type = strdup("ScrollableComponent");
  sc->proto->focusable = true;
  sc->proto->logic = logicScrollableComponent;
  sc->proto->render = renderScrollableComponent;
  sc->proto->destroy = destroyScrollableComponent;
  sc->scrollX = 0;
  sc->scrollY = 0;
  getmaxyx(stdscr, sc->scrollMaxY, sc->scrollMaxX);
  sc->component = componentToScroll;
  return sc;
}
