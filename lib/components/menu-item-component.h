#ifndef MENU_ITEM_COMPONENT_H
#define MENU_ITEM_COMPONENT_H

#include "components.h"

/**
 * \brief A menu item component.
 */
typedef struct MenuItemComponent
{
  ComponentPrototype *proto;
  char *text;
} MenuItemComponent;

/**
 * \brief Logic code for menu item component.
 * \param hc A menu item component.
 * \return An event name.
 */
char *logicMenuItemComponent(Component *_hc, int charInput);

/**
 * \brief Render code for menu item component.
 * \param hc A menu item component to render.
 */
void renderMenuItemComponent(Component *_hc);

/**
 * \brief Frees a menu item component from memory.
 * \param tic A menu item component to free.
 */
void destroyMenuItemComponent(Component *_hc);

/**
 * \brief Creates a new menu item component.
 * \return A menu item component.
 */
MenuItemComponent *createMenuItemComponent(char text[], char eventName[]);

#endif // MENU_ITEM_COMPONENT_H
