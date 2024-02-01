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
 * \brief Creates a new double input component.
 * \return A double input component.
 */
DoubleInputComponent *createDoubleInputComponent(char label[], char placeholder[], double value, double **outValue);

#endif // DOUBLE_INPUT_COMPONENT_H
