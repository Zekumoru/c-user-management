#ifndef TEXT_INPUT_COMPONENT_H
#define TEXT_INPUT_COMPONENT_H

#include "components.h"

/**
 * \brief A text input component.
 */
typedef struct TextInputComponent
{
  ComponentPrototype *proto;
  char *label;
  char *value;
  size_t valueAllocSize;
  size_t curpos;
} TextInputComponent;

/**
 * \brief Logic code for text input component.
 * \param tic A text input component.
 * \return An event name.
 */
char *logicTextInputComponent(Component *_tic, int charInput);

/**
 * \brief Render code for text input component.
 * \param tic A text input component to render.
 */
void renderTextInputComponent(Component *_tic);

/**
 * \brief Frees a text input component from memory.
 * \param tic A text input component to free.
 */
void destroyTextInputComponent(Component *_tic);

/**
 * \brief Creates a new text input component.
 * \return A text input component.
 */
TextInputComponent *createTextInputComponent(char text[], char value[], char eventName[]);

#endif // TEXT_INPUT_COMPONENT_H
