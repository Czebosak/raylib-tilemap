#include "camera_ext.hpp"

#include <raymath.h>

CameraExt::CameraExt() : render_resolution(Vector2i::zero()) {}

Vector2 CameraExt::screen_to_world(const Vector2 pos) const {
    return ((pos - this->offset) / this->zoom) + this->target;
}

Vector2 CameraExt::world_to_screen(const Vector2 pos) const {
    return ((pos - this->target) + this->offset) * this->zoom;
}
