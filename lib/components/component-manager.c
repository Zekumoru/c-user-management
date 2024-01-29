#include "../components.h"
#include "../utils.h"
#include <stdlib.h>

ComponentManager *createComponentManager()
{
  ComponentManager *cm = malloc(sizeof(ComponentManager));
  size_t size = 0;
  cm->size = size;
  cm->allocSize = size;
  cm->components = malloc(size);
  cm->indexFocusedComponent = 0;
  return cm;
}

/**
 * \brief Frees a component manager from memory.
 * \param cm A component manager to free.
 */
void destroyComponentManager(ComponentManager *cm)
{
  free(cm->components);
  free(cm);
}

void addComponent(ComponentManager *cm, Component *component)
{
  cm->components = dalloc(cm->components, sizeof(Component *), cm->size, cm->allocSize);
  cm->components[cm->size] = component;
  cm->size++;
}

bool focusComponent(ComponentManager *cm, size_t index)
{
  StubComponent *component = (StubComponent *)cm->components[index];
  StubComponent *previousComponent = (StubComponent *)cm->components[cm->indexFocusedComponent];

  if (component->proto->focusable)
  {
    previousComponent->proto->hasFocus = false;
    cm->indexFocusedComponent = index;
    component->proto->hasFocus = true;
    return true;
  }

  return false;
}
