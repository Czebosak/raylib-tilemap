#include "collisions.hpp"

bool is_colliding(const Rectanglei x, const Rectanglei y) {
    return (x.pos.x + x.size.x >= y.pos.x &&
            x.pos.x <= y.pos.x + y.size.x &&
            x.pos.y + x.size.y >= y.pos.y &&
            x.pos.y <= y.pos.y + y.size.y);
}

