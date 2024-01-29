#include "components.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

char *logicHeaderComponent(Component *_hc, int charInput)
{
  HeaderComponent *hc = (HeaderComponent *)_hc;
  return NULL;
}

void renderHeaderComponent(Component *_hc)
{
  HeaderComponent *hc = (HeaderComponent *)_hc;
  attron(A_BOLD);
  printw("%s\n", hc->text);
  attroff(A_BOLD);
}

void destroyHeaderComponent(Component *_hc)
{
  HeaderComponent *hc = (HeaderComponent *)_hc;
  destroyComponentPrototype(hc->proto);
  free(hc->text);
  free(hc);
}

HeaderComponent *createHeaderComponent()
{
  HeaderComponent *hc = malloc(sizeof(HeaderComponent));
  hc->proto = createComponentPrototype();
  hc->proto->type = strdup("HeaderComponent");
  hc->proto->eventName = NULL;
  hc->proto->focusable = false;
  hc->proto->hasFocus = false;
  hc->proto->logic = logicHeaderComponent;
  hc->proto->render = renderHeaderComponent;
  hc->proto->destroy = destroyHeaderComponent;
  hc->text = strdup("");
  return hc;
}
