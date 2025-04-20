#include <raylib.h>

#include <utils/collisions.hpp>
#include <raymath.h>
#include <cstdio>
#include <vector>
#include <boost/lexical_cast.hpp>

#include <registry.hpp>
#include <camera_ext.hpp>
#include <render.hpp>
#include <tilemap.hpp>

const float SPEED = 250.0;

int main() {
    Vector2 render_resolution = { 640.0f, 320.0f };
    Vector2 window_resolution = { 1920.0f, 1080.0f };

    InitWindow(window_resolution.x, window_resolution.y, "Hi x3");

    CameraExt camera;
    camera.render_resolution = v2tov2i(render_resolution);
    camera.target = { 0.0f, 0.0f };
    camera.offset = { render_resolution.x/2.0f, render_resolution.y/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    Vector2 player_position = { 0.0f, 0.0f };
    Texture2D player_texture = LoadTexture(ASSETS_PATH "/textures/yes_hair_bootsmoved.png");

    RenderSystem render_system;
    render_system.active_camera = &camera;

    TextureSystem texture_system;

    std::string x = "56edc9cb-21c3-4df0-93d4-d6b5ca25093d";
    auto a = boost::lexical_cast<UUID>(x);
    std::string y = "9fc3162e-eccf-4ed4-a851-f8866ca2a71c";
    auto b = boost::lexical_cast<UUID>(y);

    Registry registry;

    registry.register_tile(a, TileProperties(ASSETS_PATH "textures/dirt.png", texture_system));
    registry.register_tile(b, TileProperties(ASSETS_PATH "textures/grass.png", texture_system));

    Tilemap tilemap;

    printf("\n%d\n", tilemap.get_data_from_file(PROJECT_PATH "sd.map"));
    printf("%d, %d\n", tilemap.get_size().x, tilemap.get_size().y);

    auto data = tilemap.get_data_mut();
    data[0] = Tile(a);

    render_system.active_tilemap = &tilemap;

    RenderTexture2D screen_texture = LoadRenderTexture(640, 320);

    while (!WindowShouldClose()) {
        // Update camera stuff
        Vector2 direction = { 0.0f, 0.0f };
        if (IsKeyDown(KEY_W)) {
            direction.y -= 1.0f;
        }
        if (IsKeyDown(KEY_S)) {
            direction.y += 1.0f;
        }
        if (IsKeyDown(KEY_A)) {
            direction.x -= 1.0f;
        }
        if (IsKeyDown(KEY_D)) {
            direction.x += 1.0f;
        }

        player_position += Vector2Normalize(direction) * GetFrameTime() * SPEED;
        camera.target = player_position;

        BeginTextureMode(screen_texture);
            ClearBackground(WHITE);
            BeginMode2D(camera);
                render_system.draw_tilemap_culled(*render_system.active_tilemap, registry, texture_system);
                DrawTextureV(player_texture, player_position - Vector2 { player_texture.width/2.0f, player_texture.height/2.0f }, WHITE);
            EndMode2D();
        EndTextureMode();

        BeginDrawing();
            ClearBackground(BLACK);
            DrawTexturePro(screen_texture.texture, { 0.0f, 0.0f, render_resolution.x, -render_resolution.y }, { 0.0f, 0.0f, window_resolution.x, window_resolution.y }, { 0.0f, 0.0f }, 0.0f, WHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
