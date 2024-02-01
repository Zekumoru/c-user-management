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
 * \brief Creates a new menu item component.
 * \return A menu item component.
 */
MenuItemComponent *createMenuItemComponent(char text[], char eventName[]);

#endif // MENU_ITEM_COMPONENT_H
