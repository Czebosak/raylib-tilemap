#include "utils.hpp"
#include "raylib.h"

Vector2i::Vector2i(i32 x, i32 y) {
    this->x = x;
    this->y = y;
}

Vector2i Vector2i::zero() {
    return Vector2i(0, 0);
}

Vector2i Vector2i::operator+(const Vector2i rhs) const {
    return Vector2i(this->x + rhs.x, this->y + rhs.y);
}

Vector2i Vector2i::operator*(const Vector2i rhs) const {
    return Vector2i(this->x * rhs.x, this->y * rhs.y);
}

Vector2i Vector2i::operator*(const int rhs) const {
    return Vector2i(this->x * rhs, this->y * rhs);
}

Vector2 v2itov2(Vector2i x) {
    return Vector2 {
        (float)x.x, (float)x.y
    };
}

Vector2i v2tov2i(Vector2 x) {
    return Vector2i(x.x, x.y);
}

