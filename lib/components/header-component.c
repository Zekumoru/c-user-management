#include "components.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

Event *logicHeaderComponent(Component *_hc, int charInput)
{
  HeaderComponent *hc = (HeaderComponent *)_hc;
  return NULL;
}

void renderHeaderComponent(Component *_hc)
{
  HeaderComponent *hc = (HeaderComponent *)_hc;
  attron(A_BOLD);
  preRenderComponent(hc);
  renderComponent(hc, "%s", hc->text);
  attroff(A_BOLD);
}

void destroyHeaderComponent(Component *_hc)
{
  HeaderComponent *hc = (HeaderComponent *)_hc;
  free(hc->text);
  hc->proto->destroyProto(hc->proto);
  free(hc);
}

HeaderComponent *createHeaderComponent(char text[])
{
  HeaderComponent *hc = malloc(sizeof(HeaderComponent));
  hc->proto = createComponentPrototype();
  hc->proto->type = strdup("HeaderComponent");
  hc->proto->focusable = false;
  hc->proto->hasFocus = false;
  hc->proto->logic = logicHeaderComponent;
  hc->proto->render = renderHeaderComponent;
  hc->proto->destroy = destroyHeaderComponent;
  hc->text = strdup(text);
  return hc;
}
