#pragma once
#include <raylib.h>

#include <string>
#include <utils/utils.hpp>

class AnimatedTexture {
private:
    Texture2D texture;
    double timer;
    double duration;
    u32 frame_count;

    void update_timer();
public:
    bool paused;

    AnimatedTexture(const Texture2D texture, const u32 frame_count);
    AnimatedTexture(const std::string name, const u32 frame_count);

    void draw(const Vector2 position);
};
