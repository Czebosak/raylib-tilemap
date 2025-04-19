#pragma once

#include <unordered_map>
#include <optional>
#include <utils/uuid.hpp>

#include <tilemap.hpp>

class Registry {
private:
    std::unordered_map<UUID, TileProperties> tiles;
public:
    void clear(TextureSystem& texture_system);

    bool register_tile(UUID uuid, TileProperties tile);

    std::optional<const TileProperties*> get_tile(UUID uuid) const;

    void load_all_textures();
};
