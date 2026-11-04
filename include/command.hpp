#pragma once

#include "raylib.h"

#include <string>

enum class Shape {
    Cube,
    Sphere,
    Cylinder,
    Cone,
    Pyramid,
    Exit
};

struct SceneConfig {
    Shape shape = Shape::Cube;
    Color color = WHITE;
};

SceneConfig getUI_fc();
SceneConfig getUI_fc(const std::string& command);