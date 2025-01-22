#include "animated_texture.hpp"

void AnimatedTexture::update_timer() {
    if (!paused) {
        timer += GetTime();
    }
}

AnimatedTexture::AnimatedTexture(const Texture2D texture, const u32 frame_count) : texture(texture), timer(0.0), duration(0.0), paused(true), frame_count(frame_count) {}
AnimatedTexture::AnimatedTexture(const std::string name, const u32 frame_count) : AnimatedTexture(LoadTexture(name.c_str()), frame_count) {}

void AnimatedTexture::draw(const Vector2 position) {
    update_timer();
    DrawTextureV(texture, position, WHITE);
}

