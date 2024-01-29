#ifndef COMPONENTS_H
#define COMPONENTS_H
#define Component void

#include <stddef.h>

/**
 * \brief Manages a list of components.
 */
typedef struct ComponentManager
{
  Component **components;
  size_t size;
  size_t allocSize;
} ComponentManager;

/**
 * \brief Creates a new component manager.
 * \return A component manager.
 */
ComponentManager *createComponentManager();

/**
 * \brief Frees a component manager from memory.
 * \param cm A component manager to free.
 */
void destroyComponentManager(ComponentManager *cm);

/**
 * \brief Adds a new component to a component manager.
 * \param cm The component manager.
 * \param component The new component to add to the list.
 */
void addComponent(ComponentManager *cm, Component *component);

/**
 * \brief A basic window.
 */
typedef struct Window
{
  ComponentManager *cm;
} Window;

Window *createWindow();
void destroyWindow(Window *win);

/**
 * \brief Manages a stack of windows.
 */
typedef struct WindowManager
{
  Window *current;
  Window **windows;
  size_t size;
  size_t allocSize;
} WindowManager;

WindowManager *createWindowManager();

void pushWindow(WindowManager *wm, Window *win);
void popWindow(WindowManager *wm);

#endif // COMPONENTS_H
