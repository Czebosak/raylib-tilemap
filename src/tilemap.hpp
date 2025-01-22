#pragma once
#include <raylib.h>

#include <optional>
#include <string>
#include <memory>
#include <span>

#include "utils/utils.hpp"

#define TILEMAP_SIZE 1024

class TileProperties {
private:
    std::string texture_path;
    Texture texture;
public:
    TileProperties(const std::string texture_path);

    const Texture& get_texture() const;

    void load_texture();
};

class Tile {
private:
    u32 id;
public:
    Tile();

    Tile(u32 id);

    inline u32 get_id() {
        return id;
    }
};

#define TILEMAP_CHUNK_SIZE 16

struct TilemapChunk {
    Tile* tile[TILEMAP_CHUNK_SIZE];
};

class Tilemap {
private:
    Vector2i size;
    Vector2i tile_size;
    std::unique_ptr<Tile[]> data;
    std::span<TileProperties> tile_properties;
public:
    Tilemap(std::span<TileProperties> tile_properties);

    Vector2i get_size() const;

    Vector2i get_tile_size() const;

    Vector2i fetch_tile_size() const;

    int get_data_from_file(const std::string filename);

    inline Vector2i convert_index_to_tile_position(const u32 i) const {
        return Vector2i(i % size.y, i / size.y);
    }

    inline TileProperties& get_tile_properties(const u32 id) const {
        return tile_properties[id];
    }

    inline std::optional<Tile> get_tile(u32 x, u32 y) const {
        if ((x < size.x) && (y < size.y)) {
            return data[y * size.x + x];
        }
        return {};
    }

    inline std::span<Tile> get_data() {
        return std::span<Tile>(data.get(), size.x * size.y);
    }

    TilemapChunk get_chunk(u32 x, u32 y);

    Vector2i tile_position_to_world_position(const Vector2i pos) const;
    Vector2i chunk_to_tile_pos(Vector2i chunk_pos, Vector2i tile_pos) const;
};

