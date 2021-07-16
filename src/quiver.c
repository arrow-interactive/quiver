#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "quiver.h"

Registry* CreateRegistry(unsigned int max_ent) {
    Registry* reg = malloc(sizeof(Registry));
    reg->max_entities = max_ent;
    reg->active_entities = 0;
    reg->destroyed_entities = 0;
    reg->destroyed_entity_array = malloc(max_ent * sizeof(Entity));
    reg->signatures = malloc(max_ent * sizeof(Signature));

    reg->total_component_types = 0;
    // Allocate space for 32 components:
    reg->component_sizes = malloc(32 * sizeof(int));
    reg->components_array = malloc(32 * sizeof(int));
    return reg;
}

ComponentType RegisterComponentType(Registry* reg, size_t c_size) {
    if (reg->total_component_types == 32) {
        printf("[QVR::RegisterComponentType()]: Component limit exceeded!\n");
        return 0;
    }
    reg->component_sizes[reg->total_component_types] = c_size;
    reg->components_array[reg->total_component_types] = malloc(reg->max_entities * c_size);
    return 1 << reg->total_component_types++;
}

void ReAllocateMem(Registry* reg) {
    reg->max_entities *= 2;
    Entity* old_dea = reg->destroyed_entity_array;
    reg->destroyed_entity_array = realloc(old_dea, reg->max_entities * sizeof(Entity));
}

Entity CreateEntity(Registry* reg, Signature sig) {
    // Assume that the signature at index i
    // corresponds to the entity i for now.
    // TODO: Implement lookup table here.
    if (reg->active_entities == reg->max_entities)
        ReAllocateMem(reg);

    if (reg->destroyed_entities > 0) {
        Entity new_entity = reg->destroyed_entity_array[--reg->destroyed_entities];
        reg->signatures[new_entity] = sig;
        return new_entity;
    }
    reg->signatures[reg->active_entities] = sig;
    return reg->active_entities++;
}

void DestroyEntity(Registry* reg, Entity ent) {
    // TODO: Use lookup table to delete the
    // components of this entity too.
    if (ent > reg->active_entities - 1) {
        printf("[QVR::DestroyEntity()]: Cannot destroy non-existent entities. Ignoring...\n");
        return;
    }
    for (int i = 0; i < reg->destroyed_entities; i++) {
        if (reg->destroyed_entity_array[i] == ent) {
            printf("[QVR::DestroyEntity()]: Cannot destroy already-destroyed entities. Ignoring...\n");
            return;
        }
    }
    reg->destroyed_entity_array[reg->destroyed_entities++] = ent;
}

void AddComponent(Registry* reg, Entity ent, ComponentType ct) {
    // Assume that the signature at index i
    // corresponds to the entity i for now.
    // TODO: Implement lookup table here.
    reg->signatures[ent] |= ct;
}

u8 HasComponents(Registry* reg, Entity ent, Signature sig) {
    // Assume that the signature at index i
    // corresponds to the entity i for now.
    // TODO: Implement lookup table here.
    return (reg->signatures[ent] & sig) == sig;
}

int GetComponentIndex(ComponentType ct) {
    // TODO: Use better logic
    // for more efficiency.
    return (int)log2(ct);
}

void* GetComponent(Registry* reg, Entity ent, ComponentType ct) {
    // Assume that the component at index i
    // corresponds to the entity i for now.
    // TODO: Implement lookup table here.
    int ct_index = GetComponentIndex(ct);
    return reg->components_array[ct_index] + (reg->component_sizes[ct_index] * ent);
}
