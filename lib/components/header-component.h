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
 * \brief Logic code for header component.
 * \param hc A header component.
 * \return An event name.
 */
char *logicHeaderComponent(Component *_hc, int charInput);

/**
 * \brief Render code for header component.
 * \param hc A header component to render.
 */
void renderHeaderComponent(Component *_hc);

/**
 * \brief Frees a header component from memory.
 * \param tic A header component to free.
 */
void destroyHeaderComponent(Component *_hc);

/**
 * \brief Creates a new header component.
 * \return A header component.
 */
HeaderComponent *createHeaderComponent();

#endif // HEADER_COMPONENT_H
