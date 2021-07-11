#ifndef PECS_H
#define PECS_H

#include <stdlib.h>

#define NO_COMPONENTS 0

typedef unsigned int Entity, ComponentType, Signature;

typedef struct Registry {
    // Entities related:
    Entity total_entities;
    Signature* signatures;

    // Components related:
    ComponentType total_component_types;
    size_t* component_sizes;
    void** components_array;
} Registry;

Registry* CreateRegistry();
ComponentType RegisterComponentType(Registry* reg, size_t c_size);

#endif  // PECS_H
