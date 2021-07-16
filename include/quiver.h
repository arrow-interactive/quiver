#ifndef QUIVER_H
#define QUIVER_H

#include <stdint.h>
#include <stdlib.h>

#define NO_COMPONENTS 0

typedef unsigned char u8;
typedef uint32_t Entity, ComponentType, Signature;

typedef struct Registry {
    // Entities related:
    Entity max_entities;
    Entity active_entities;
    Entity destroyed_entities;
    Entity* destroyed_entity_array;
    Signature* signatures;

    // Components related:
    ComponentType total_component_types;
    size_t* component_sizes;
    void** components_array;
} Registry;

Registry* CreateRegistry(unsigned int max_ent);
ComponentType RegisterComponentType(Registry* reg, size_t c_size);
void ReAllocateMem(Registry* reg);

// Entities related:
Entity CreateEntity(Registry* reg, Signature sig);
void DestroyEntity(Registry* reg, Entity ent);

// Components related:
void AddComponent(Registry* reg, Entity ent, ComponentType ct);
u8 HasComponents(Registry* reg, Entity ent, Signature sig);
int GetComponentIndex(ComponentType ct);
void* GetComponent(Registry* reg, Entity ent, ComponentType ct);

#endif  // QUIVER_H
