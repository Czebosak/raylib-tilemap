#pragma once
#include <vector>

#include <registry.hpp>
#include <tilemap.hpp>
#include <camera_ext.hpp>

class TilemapRenderer {
private:
    struct RenderedChunk {
        int x;
        int y;
        Texture2D texture;
    };

    std::vector<RenderedChunk> rendered_chunks;

    bool chunk_is_visible(u32 i) const;
    Rectanglei get_visible_chunks() const;
public:
    bool chunk_is_visible(const Vector2i pos) const;
    Tilemap* active_tilemap;
    CameraExt* active_camera;

    void draw_tilemap_culled(const Tilemap& tilemap, const Registry& registry, TextureSystem& texture_system) const;
};
