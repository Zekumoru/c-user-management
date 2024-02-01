#ifndef TEXT_INPUT_COMPONENT_H
#define TEXT_INPUT_COMPONENT_H

#include "components.h"

/**
 * \brief A text input component.
 */
typedef struct TextInputComponent
{
  ComponentPrototype *proto;
  struct InputComponentPrototype *ic_proto;
  char *value;
} TextInputComponent;

/**
 * \brief Creates a new text input component.
 * \return A text input component.
 */
TextInputComponent *createTextInputComponent(char label[], char placeholder[], char value[], char eventName[], char **outValue);

#endif // TEXT_INPUT_COMPONENT_H
