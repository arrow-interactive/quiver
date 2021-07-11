#include <stdlib.h>
#include <stdio.h>
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
        printf("[Quiver::RegisterComponentType()]: There can only be 32 component types. Not registering the 33rd one.\n");
        return 0;
    }
    reg->component_sizes[reg->total_component_types] = c_size;
    return 1 << reg->total_component_types++;
}

Entity CreateEntity(Registry* reg, Signature sig) {
    // Assume that the signature at index i
    // corresponds to the entity i for now.
    // TODO: Implement lookup table here.
    reg->signatures[reg->total_entities] = sig;
    return reg->total_entities++;
}
