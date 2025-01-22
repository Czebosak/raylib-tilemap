#pragma once
#include <raylib.h>

#include <utils/utils.hpp>

class CameraExt : public Camera2D {
public:
    Vector2i render_resolution;

    CameraExt();

    Vector2 screen_to_world(const Vector2 pos) const;
    Vector2 world_to_screen(const Vector2 pos) const;
};
