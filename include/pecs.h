#ifndef PECS_H
#define PECS_H

#include <stdlib.h>

typedef unsigned int Entity, ComponentType, Signature;

typedef struct Registry {
    // Entities related:
    Entity total_entities;
    Signature* signatures;

    // Components related:
    ComponentType total_component_types;
    size_t* component_sizes;
    void** components;
} Registry;

Registry* CreateRegistry();
ComponentType RegisterComponentType(Registry* reg, size_t c_size);

#endif  // PECS_H
