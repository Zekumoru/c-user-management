#include "../components.h"
#include "../utils.h"
#include <stdlib.h>

void addComponent_CM(ComponentManager *cm, Component *component)
{
  cm->components = dalloc(cm->components, sizeof(Component *), cm->size, cm->allocSize);
  cm->components[cm->size] = component;
  cm->size++;
}

bool focusComponent_CM(ComponentManager *cm, size_t index)
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

// returns true if a component has been removed
bool removeComponent_CM(ComponentManager *cm, size_t indexToRemove)
{
  // first check if the index exists
  if (indexToRemove >= cm->size || indexToRemove < 0)
  {
    return false;
  }

  // create a temporary new components array and put everything there
  // except the component to delete
  size_t newSize = cm->size - 1;
  Component **newComponents = malloc(sizeof(Component *) * newSize);
  for (size_t i = 0, j = 0; i < cm->size; i++)
  {
    if (i == indexToRemove)
    {
      // ignore this component since it is to be removed
      StubComponent *component = (StubComponent *)cm->components[i];
      component->proto->destroy(component);
      j++; // this is used to like "skip" the removed element
      continue;
    }

    newComponents[i - j] = cm->components[i];
  }

  // check if possible to divide allocSize by 2
  if (newSize <= (cm->allocSize / 2))
  {
    cm->allocSize /= 2;
  }

  // move the new components to component manager and also free the old one
  free(cm->components);
  cm->components = newComponents;
  cm->size = newSize;

  return true;
}

void destroyComponentManager(ComponentManager *cm)
{
  // free individual components from memory
  for (size_t i = 0; i < cm->size; i++)
  {
    StubComponent *component = (StubComponent *)cm->components[i];
    component->proto->destroy(component);
  }

  free(cm->components);
  free(cm);
}

ComponentManager *createComponentManager()
{
  ComponentManager *cm = malloc(sizeof(ComponentManager));
  size_t size = 0;
  cm->size = size;
  cm->allocSize = size;
  cm->components = malloc(size);
  cm->indexFocusedComponent = 0;
  cm->addComponent = addComponent_CM;
  cm->removeComponent = removeComponent_CM;
  cm->focusComponent = focusComponent_CM;
  cm->destroy = destroyComponentManager;
  return cm;
}
