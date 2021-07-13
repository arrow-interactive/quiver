#ifndef QUIVER_H
#define QUIVER_H

#include <stdlib.h>

#define NO_COMPONENTS 0

typedef unsigned char u8;
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
Entity CreateEntity(Registry* reg, Signature sig);
u8 HasComponents(Registry* reg, Entity ent, Signature sig);
int GetComponentIndex(ComponentType ct);
void* GetComponent(Registry* reg, Entity ent, ComponentType ct);

#endif  // QUIVER_H
