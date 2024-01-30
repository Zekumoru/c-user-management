#include "components.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

bool validateTextInputComponent(char *input, int charInput)
{
  // if char input is not a valid printable character
  if (charInput < 32 || charInput > 255)
  {
    return false;
  }

  return true;
}

char *logicTextInputComponent(Component *_tic, int charInput)
{
  TextInputComponent *tic = (TextInputComponent *)_tic;
  return tic->ic_proto->logic(tic->ic_proto, tic->proto, charInput, validateTextInputComponent);
}

void renderTextInputComponent(Component *_tic)
{
  TextInputComponent *tic = (TextInputComponent *)_tic;
  tic->ic_proto->render(tic->ic_proto, tic->proto);
}

void destroyTextInputComponent(Component *_tic)
{
  TextInputComponent *tic = (TextInputComponent *)_tic;
  destroyComponentPrototype(tic->proto);
  free(tic);
}

TextInputComponent *createTextInputComponent(char label[], char placeholder[], char value[], char eventName[], char **outValue)
{
  TextInputComponent *tic = malloc(sizeof(TextInputComponent));
  tic->proto = createComponentPrototype();
  tic->proto->type = strdup("TextInputComponent");
  tic->proto->eventName = strdup(eventName);
  tic->proto->focusable = true;
  tic->proto->logic = logicTextInputComponent;
  tic->proto->render = renderTextInputComponent;
  tic->proto->destroy = destroyTextInputComponent;
  tic->ic_proto = createInputComponentPrototype(label, placeholder, value);
  tic->value = tic->ic_proto->input;
  *outValue = tic->ic_proto->input;
  return tic;
}
