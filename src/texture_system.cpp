#include "texture_system.hpp"

Texture* TextureSystem::get_or_load_texture(const std::string path) {
    auto it = data.find(path);
    if (it == data.end()) {
        data[path] = LoadTexture(path.c_str());
        return &data[path];
    }

    return &it->second;
}

