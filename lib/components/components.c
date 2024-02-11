#include "components.h"
#include "../vrender.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

void init()
{
  initscr();
  noecho();
  cbreak();
  keypad(stdscr, true);
  curs_set(0);
}

void run(Component *__component)
{
  StubComponent *component = (StubComponent *)__component;

  int charInput = 0;
  Event *event;
  while (true)
  {
    // Logic
    event = component->proto->logic(component, charInput);
    if (event != NULL && strcmp(event->name, "exit") == 0)
    {
      break;
    }

    // Render
    clear();
    component->proto->render(component);
    refresh();

    // Input
    charInput = getch();

    // Cleanup
    if (event != NULL)
    {
      event->destroy(event);
      event = NULL;
    }
  }

  // Cleanup and exit
  component->proto->destroy(component);
  if (event != NULL)
  {
    event->destroy(event);
  }
}

void cleanup()
{
  standend();
  endwin();
}

void preRenderComponent(Component *__component)
{
  StubComponent *component = (StubComponent *)__component;
  ComponentPrototype *proto = component->proto;
  proto->renderX = proto->screenX;
  proto->renderY = proto->screenY;
}

void renderComponent(Component *__component, const char *__format, ...)
{
  StubComponent *component = (StubComponent *)__component;
  ComponentPrototype *proto = component->proto;

  // get format arguments
  va_list args;
  va_start(args, __format);
  vrmn_mvvwprintw(
      stdscr,
      &proto->renderY, &proto->renderX,
      proto->screenMaxY, proto->screenMaxX,
      proto->autoNewline, __format, args);
  va_end(args);
}
