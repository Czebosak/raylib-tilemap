#include "tilemap.hpp"

#include <texture_system.hpp>
#include <fstream>
#include <memory>

TileProperties::TileProperties(const std::string texture_path, TextureSystem& texture_system) : texture_path(texture_path), texture(*texture_system.get_or_load_texture(texture_path)), dynamic_tile(false) {}

TileProperties::TileProperties(const std::string texture_path, TextureSystem& texture_system, bool dynamic_tile) : texture_path(texture_path), texture(*texture_system.get_or_load_texture(texture_path)), dynamic_tile(dynamic_tile) {}

const Texture& TileProperties::get_texture(TextureSystem& texture_system) const {
    if (texture.id == 0) {
    }

    return texture;
}

void TileProperties::load_texture() {
    texture = LoadTexture(texture_path.c_str());
}

Tile::Tile() : uuid(uuids::nil_uuid()) {}

Tile::Tile(UUID uuid) : uuid(uuid) {}

UUID Tile::get_uuid() const {
    return uuid;
}

Tilemap::Tilemap() : size(Vector2i::zero()), tile_size(Vector2i::zero()), data() {}

Vector2i Tilemap::get_size() const {
    return size;
}

Vector2i Tilemap::get_tile_size() const {
    return tile_size;
}

Vector2i Tilemap::fetch_tile_size() const {
    /*Texture texture = tile_properties[0].get_texture();*/
    /*return Vector2i(texture.width, texture.height);*/
    return Vector2i(16, 16);
}

int Tilemap::get_data_from_file(const std::string filename) {
    std::ifstream s(filename, std::ifstream::binary);

    s.read(reinterpret_cast<char*>(&size.x), sizeof(size.x));
    s.read(reinterpret_cast<char*>(&size.y), sizeof(size.y));

    data = std::make_unique<Tile[]>(size.x * size.y);

    for (int i = 0; i < size.x * size.y; i++) {
        if (!s.read(reinterpret_cast<char*>(&data.get()[i]), sizeof(data[i]))) {
            return 1;
        }
    }

    tile_size = fetch_tile_size();

    return 0;
}

TilemapChunk Tilemap::get_chunk(u32 x, u32 y) const {
    TilemapChunk chunk;

    // Fill the chunk with a pointer to each row
    for (int i = 0; i < TILEMAP_CHUNK_SIZE; i++) {
        int a = ((x * TILEMAP_CHUNK_SIZE) + (y * TILEMAP_CHUNK_SIZE * this->size.x)) + (i * this->size.x);
        chunk.tile[i] = &this->data[a];
    }

    return chunk;
}

TilemapChunkMut Tilemap::get_chunk_mut(u32 x, u32 y) {
    TilemapChunkMut chunk;

    // Fill the chunk with a pointer to each row
    for (int i = 0; i < TILEMAP_CHUNK_SIZE; i++) {
        int a = ((x * TILEMAP_CHUNK_SIZE) + (y * TILEMAP_CHUNK_SIZE * this->size.x)) + (i * this->size.x);
        chunk.tile[i] = &this->data[a];
    }

    return chunk;
}

Vector2i Tilemap::tile_position_to_world_position(const Vector2i pos) const {
    return pos * this->get_tile_size();
}

Vector2i Tilemap::chunk_to_tile_pos(Vector2i chunk_pos, Vector2i tile_pos) const {
    Vector2i chunk_size = this->get_tile_size() * TILEMAP_CHUNK_SIZE;
    return (chunk_pos * chunk_size) + (tile_pos * this->get_tile_size());
}

