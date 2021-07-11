// Include pecs.h and compile
// pecs.c along with your project.
#include "pecs.h"

// Define your components as structs.
typedef struct Transform {
    int x, y;
} Transform;

typedef struct Health {
    int health;
} Health;
// There can be a maximum of 32 components.

int main() {
    // Create a registry like this. The registry
    // will contain the state of the entire ECS.
    Registry* reg = CreateRegistry();

    // Register your components like this. ComponentTypes are
    // unsigned integers. It is required to pass the Registry
    // pointer so that the component can be registered within it.
    ComponentType transform = RegisterComponentType(reg, sizeof(Transform));
    ComponentType health = RegisterComponentType(reg, sizeof(Health));
    // Once registered, you can use the returned ComponentType to
    // refer to the registered component while constructing signatures.

    // Create entities like this. Again, a Registry pointer is needed.
    // Pass the signature of the entity while creating it, or pass 
    // NO_COMPONENTS to create an empty entity.
    Entity player = CreateEntity(reg, transform + health);
    // player is an Entity with Transform and Health components.
    Entity empty = CreateEntity(reg, NO_COMPONENTS);
    // Pass NO_COMPONENTS as the signature to create
    // an entity with no components (empty entity).

    // You can check if an entity has atleast a certain combination
    // of entities by using HasComponents. Pass the Registry pointer,
    // the entity itself, and finally the signature to check for.
    if (HasComponents(reg, player, transform + health)) {
        // Do something.
    }

    // Finally, to Access a component of an entity, simply
    // call GetComponent with the Registry pointer, the entity
    // itself, and finally the component you want to grab.
    Health* player_health = GetComponent(reg, player, health);

    // TODO: Design AddComponent, RemoveComponent and DestroyEntity.
}
