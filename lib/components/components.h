#ifndef COMPONENTS_COMPONENTS_H
#define COMPONENTS_COMPONENTS_H

#define Component void
#define Window void

#include <stdarg.h>

#include "event.h"
#include "component-manager.h"
#include "component-prototype.h"
#include "stub-component.h"
#include "window-component.h"
#include "stub-window.h"
#include "window-manager-component.h"
#include "header-component.h"
#include "menu-item-component.h"
#include "input-prototype-component.h"
#include "text-input-component.h"
#include "double-input-component.h"

void init();
void run(Component *__component);
void cleanup();

void preRenderComponent(Component *__component);
void renderComponent(Component *__component, const char *__format, ...);

#endif // COMPONENTS_COMPONENTS_H
