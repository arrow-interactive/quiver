#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "pecs.h"

Registry* CreateRegistry() {
    Registry* reg = malloc(sizeof(Registry));
    reg->total_entities = 0;
    // Allocate enough memory for 10 entities for now:
    reg->signatures = malloc(10 * sizeof(Signature));

    reg->total_component_types = 0;
    // Allocate space for 32 components:
    reg->component_sizes = malloc(32 * sizeof(int));
    reg->components_array = malloc(32 * sizeof(int));
    return reg;
}

ComponentType RegisterComponentType(Registry* reg, size_t c_size) {
    if (reg->total_component_types == 32) {
        printf("[Quiver::RegisterComponentType()]: Component limit exceeded!\n");
        return 0;
    }
    reg->component_sizes[reg->total_component_types] = c_size;
    reg->components_array[reg->total_component_types] = malloc(10 * c_size);
    return 1 << reg->total_component_types++;
}

Entity CreateEntity(Registry* reg, Signature sig) {
    // Assume that the signature at index i
    // corresponds to the entity i for now.
    // TODO: Implement lookup table here.
    reg->signatures[reg->total_entities] = sig;
    return reg->total_entities++;
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
