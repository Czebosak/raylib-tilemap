#pragma once
#include <raylib.h>

#include <string>
#include <unordered_map>

class TextureSystem {
private:
    std::unordered_map<std::string, Texture> data;
public:
    Texture* get_or_load_texture(const std::string path);
};
