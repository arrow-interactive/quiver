#include <stdlib.h>
#include "pecs.h"

Registry* CreateRegistry() {
    Registry* reg = malloc(sizeof(Registry));
    reg->total_entities = 0;
    // Allocate enough memory for 10 entities for now:
    reg->signatures = malloc(10 * sizeof(Signature));

    reg->total_component_types = 0;
    // Allocate space for 32 components:
    reg->component_sizes = malloc(32 * sizeof(int));
    reg->components = malloc(32 * sizeof(int));
    return reg;
}

ComponentType RegisterComponentType(Registry* reg, size_t c_size) {
    reg->component_sizes[reg->total_component_types] = c_size;
    return 1 << reg->total_component_types++;
}
