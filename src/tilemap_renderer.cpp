#include "tilemap_renderer.hpp"
#include "texture_system.hpp"

#include <utils/utils.hpp>
#include <utils/collisions.hpp>

#include <tilemap.hpp>

bool TilemapRenderer::chunk_is_visible(const Vector2i pos) const {
    Vector2i chunk_size = active_tilemap->get_tile_size() * TILEMAP_CHUNK_SIZE;

    // Calculate the position of the first tile of the chunk
    Vector2i world_chunk_pos = pos * chunk_size;

    // Calculate the screen position of the chunk
    Vector2i screen_chunk_pos = v2tov2i(active_camera->world_to_screen(v2itov2(world_chunk_pos)));

    Rectanglei screen_chunk_rec = Rectanglei(screen_chunk_pos, chunk_size);

    // Create the camera screen rec
    Rectanglei screen_rec = Rectanglei { Vector2i(0, 0), active_camera->render_resolution };

    return is_colliding(screen_rec, screen_chunk_rec);
}

void TilemapRenderer::draw_tilemap(Tilemap& tilemap) const {
    std::span<Tile> data = tilemap.get_data();

    for (int i; i < data.size(); i++) {
        Tile tile = data[i];
        TileProperties& tile_properties = tilemap.get_tile_properties(tile.get_id());

        /*Vector2 position = v2itov2(tilemap.convert_index_to_tile_position(i) * tile_properties.get_texture().width);*/

        /*DrawTextureEx(tile_properties.get_texture(), position, 0.0f, 1.0f, WHITE);*/
    }
}

void TilemapRenderer::draw_tilemap_culled(Tilemap& tilemap, TextureSystem& texture_system) const {
    std::span<Tile> data = tilemap.get_data();

    for (u32 chunk_x = 0; chunk_x < tilemap.get_size().x / 16; chunk_x++) {
        for (u32 chunk_y = 0; chunk_y < tilemap.get_size().y / 16; chunk_y++) {
            if (chunk_is_visible(Vector2i(chunk_x, chunk_y))) {
                TilemapChunk chunk = tilemap.get_chunk(chunk_x, chunk_y);

                for (int tile_x = 0; tile_x < TILEMAP_CHUNK_SIZE; tile_x++) {
                    for (int tile_y = 0; tile_y < TILEMAP_CHUNK_SIZE; tile_y++) {
                        Tile tile = chunk.tile[tile_x][tile_y];
                        TileProperties& tile_properties = tilemap.get_tile_properties(tile.get_id());

                        Vector2 position = v2itov2(tilemap.chunk_to_tile_pos(Vector2i(chunk_x, chunk_y), Vector2i(tile_x, tile_y)));

                        DrawTextureEx(tile_properties.get_texture(texture_system), position, 0.0f, 1.0f, WHITE);
                    }
                }
            }
        }
    }
}

