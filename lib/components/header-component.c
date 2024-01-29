#include "components.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

void logicHeaderComponent(Component *_hc, int charInput)
{
  HeaderComponent *hc = (HeaderComponent *)_hc;
}

void renderHeaderComponent(Component *_hc)
{
  HeaderComponent *hc = (HeaderComponent *)_hc;
  attron(A_BOLD);
  printw("%s\n", hc->text);
  attroff(A_BOLD);
}

void deleteHeaderComponent(Component *_hc)
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
  hc->proto->focusable = false;
  hc->proto->logic = logicHeaderComponent;
  hc->proto->render = renderHeaderComponent;
  hc->proto->delete = deleteHeaderComponent;
  hc->text = strdup("");
  return hc;
}
