#include "collisions.hpp"

bool is_colliding(const Rectanglei x, const Rectanglei y) {
    /*return (x.pos.x + x.size.x > y.pos.x &&          // Right edge of x is after left edge of y*/
    /*        y.pos.x + y.size.x > x.pos.x &&          // Right edge of y is after left edge of x*/
    /*        x.pos.y + x.size.y > y.pos.y &&          // Bottom edge of x is after top edge of y*/
    /*        y.pos.y + y.size.y > x.pos.y);           // Bottom edge of y is after top edge of x*/
    return (x.pos.x < y.pos.x + y.size.x &&      // x's right is to the left of y's right
        x.pos.x + x.size.x > y.pos.x &&          // x's left is to the right of y's left
        x.pos.y < y.pos.y + y.size.y &&          // x's bottom is below y's top
        x.pos.y + x.size.y > y.pos.y);           // x's top is above y's bottom
}

