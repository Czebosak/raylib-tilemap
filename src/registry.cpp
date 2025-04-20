#include "registry.hpp"
#include <raylib.h>

#include <texture_system.hpp>

void Registry::clear(TextureSystem& texture_system) {
    for (auto& entry : tiles) {
        UnloadTexture(entry.second.get_texture(texture_system));
    }
    tiles.clear();
}

bool Registry::register_tile(UUID uuid, TileProperties tile) {
    auto result = tiles.emplace(uuid, tile);
    return result.second;
}

std::optional<const TileProperties*> Registry::get_tile(UUID uuid) const {
    auto it = tiles.find(uuid);
    if (it == tiles.end()) return std::nullopt;
    return std::make_optional(&(it->second));
}

void Registry::load_all_textures() {
    for (auto& entry : tiles) {
        entry.second.load_texture();
    }
}
