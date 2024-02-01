#ifndef HEADER_COMPONENT_H
#define HEADER_COMPONENT_H

#include "components.h"

/**
 * \brief A header component.
 */
typedef struct HeaderComponent
{
  ComponentPrototype *proto;
  char *text;
} HeaderComponent;

/**
 * \brief Creates a new header component.
 * \return A header component.
 */
HeaderComponent *createHeaderComponent(char text[]);

#endif // HEADER_COMPONENT_H
