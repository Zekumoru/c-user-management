#include "components.h"
#include "../utils.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

bool validateDoubleInputComponent(char *input, int charInput)
{
  // if char input is not a valid printable character
  if ((charInput < '0' || charInput > '9') && charInput != '.')
  {
    return false;
  }

  // if there's already a dot then ignore
  if (strchr(input, '.') && charInput == '.')
  {
    return false;
  }

  return true;
}

Event *logicDoubleInputComponent(Component *_dic, int charInput)
{
  DoubleInputComponent *dic = (DoubleInputComponent *)_dic;
  Event *event = dic->ic_proto->logic(dic->ic_proto, dic, charInput, validateDoubleInputComponent);
  dic->value = toDouble(dic->ic_proto->input);
  return event;
}

void renderDoubleInputComponent(Component *_dic)
{
  DoubleInputComponent *dic = (DoubleInputComponent *)_dic;
  dic->ic_proto->render(dic->ic_proto, dic);
}

void destroyDoubleInputComponent(Component *_dic)
{
  DoubleInputComponent *dic = (DoubleInputComponent *)_dic;
  dic->ic_proto->destroy(dic->ic_proto);
  dic->proto->destroyProto(dic->proto);
  free(dic);
}

DoubleInputComponent *createDoubleInputComponent(char label[], char placeholder[], double value)
{
  DoubleInputComponent *dic = malloc(sizeof(DoubleInputComponent));
  dic->proto = createComponentPrototype();
  dic->proto->type = strdup("DoubleInputComponent");
  dic->proto->focusable = true;
  dic->proto->logic = logicDoubleInputComponent;
  dic->proto->render = renderDoubleInputComponent;
  dic->proto->destroy = destroyDoubleInputComponent;
  char valueString[100] = "";
  if (value != 0)
  {
    sprintf(valueString, "%.2lf", value);
  }
  dic->ic_proto = createInputComponentPrototype(label, placeholder, valueString, NULL);
  return dic;
}
