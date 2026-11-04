#pragma once

#include "vector.hpp"
#include "command.hpp"

#include <cmath>

void render(SceneConfig config);
Vec3 rotateX(const Vec3& v, float angle);
Vec3 rotateY(const Vec3& v, float angle);