#ifndef DOUBLE_INPUT_COMPONENT_H
#define DOUBLE_INPUT_COMPONENT_H

#include "components.h"

/**
 * \brief A double input component.
 */
typedef struct DoubleInputComponent
{
  ComponentPrototype *proto;
  struct InputComponentPrototype *ic_proto;
  double value;
} DoubleInputComponent;

/**
 * \brief Logic code for double input component.
 * \param tic A double input component.
 * \return An event name.
 */
char *logicDoubleInputComponent(Component *_tic, int charInput);

/**
 * \brief Render code for double input component.
 * \param tic A double input component to render.
 */
void renderDoubleInputComponent(Component *_tic);

/**
 * \brief Frees a double input component from memory.
 * \param tic A double input component to free.
 */
void destroyDoubleInputComponent(Component *_tic);

/**
 * \brief Creates a new double input component.
 * \return A double input component.
 */
DoubleInputComponent *createDoubleInputComponent(char label[], double value, char eventName[], double **outValue);

#endif // DOUBLE_INPUT_COMPONENT_H
