#include "renderer.hpp"
#include "geometry.hpp"
#include "vector.hpp"

#include "raylib.h"

#include <cmath>

const float FIELD_SIZE = 10.0f;

Vec3 rotateX(const Vec3& v, float angle) {
    return {v.x, v.y * cosf(angle) - v.z * sinf(angle), v.y * sinf(angle) + v.z * cosf(angle)};
}

Vec3 rotateY(const Vec3& v, float angle) {
    return {v.x * cosf(angle) - v.z * sinf(angle), v.y, v.x * sinf(angle) + v.z * cosf(angle)};
}

void render(SceneConfig config) {

    SetTraceLogLevel(LOG_NONE);
      
    auto points = generateShapePoints(config.shape);
    
    std::vector<Vec3> result;
    for (const auto& point : points) {
        result.push_back(rotateX(point, -0.4));
    }
    points = result;
    
    InitWindow(800, 600, "My Renderer");
    SetTargetFPS(60);

    float angle = 0.0f;

    while (!WindowShouldClose()) {

        angle += 1.0f * GetFrameTime();

        BeginDrawing();
        ClearBackground(BLACK);

        for (auto point: points){
            Vec3 rotated = rotateY(point, angle);

            float screenX = 400 + 400.0f * rotated.x / (rotated.z + 10.0f);
            float screenY = 300 - 400.0f * rotated.y / (rotated.z + 10.0f);

            DrawCircle(screenX, screenY, 2, config.color);
        }

        EndDrawing();
    }

    CloseWindow();
}



