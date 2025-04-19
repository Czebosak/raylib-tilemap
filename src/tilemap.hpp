#pragma once
#include <raylib.h>

#include <texture_system.hpp>
#include <utils/uuid.hpp>
#include <utils/uuid_generators.hpp>
#include <optional>
#include <string>
#include <memory>
#include <span>

#include "utils/utils.hpp"

#define TILEMAP_SIZE 1024

class TileProperties {
private:
    std::string texture_path;
    mutable Texture texture;
    bool dynamic_tile;
public:
    TileProperties(const std::string texture_path, TextureSystem& texture_system);
    TileProperties(const std::string texture_path, TextureSystem& texture_system, bool dynamic_tile);

    const Texture& get_texture(TextureSystem& texture_system) const;

    void load_texture();
};

class Tile {
private:
    UUID uuid;
public:
    Tile();
    Tile(UUID uuid);

    UUID get_uuid() const;
};

#define TILEMAP_CHUNK_SIZE 16

struct TilemapChunk {
    const Tile* tile[TILEMAP_CHUNK_SIZE];
};

struct TilemapChunkMut {
    Tile* tile[TILEMAP_CHUNK_SIZE];
};

class Tilemap {
private:
    Vector2i size;
    Vector2i tile_size;
    std::unique_ptr<Tile[]> data;
public:
    Tilemap();

    Vector2i get_size() const;

    Vector2i get_tile_size() const;

    Vector2i fetch_tile_size() const;

    int get_data_from_file(const std::string filename);

    inline Vector2i convert_index_to_tile_position(const u32 i) const {
        return Vector2i(i % size.y, i / size.y);
    }

    std::optional<Tile*> get_tile(u32 x, u32 y) const {
        if ((x < size.x) && (y < size.y)) {
            return std::make_optional(&data[y * size.x + x]);
        }
        return std::nullopt;
    }

    std::span<const Tile> get_data() const {
        return std::span<Tile>(data.get(), size.x * size.y);
    }

    std::span<Tile> get_data_mut() {
        return std::span<Tile>(data.get(), size.x * size.y);
    }

    TilemapChunk get_chunk(u32 x, u32 y) const;
    
    TilemapChunkMut get_chunk_mut(u32 x, u32 y);

    Vector2i tile_position_to_world_position(const Vector2i pos) const;
    Vector2i chunk_to_tile_pos(Vector2i chunk_pos, Vector2i tile_pos) const;
};

