#include "world.h"

World* World::Instance() {
    if(!world) {
        world = new World();
    }
    return world;
}
