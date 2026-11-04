#pragma once

#include "vector.hpp"
#include "command.hpp"

#include <vector>
#include <utility>

std::vector<Vec3> createCube(float halfSize);
std::vector<std::pair<int, int>> createCubeEdges(const std::vector<Vec3>& vertices);
std::vector<Vec3> generatePoints(const std::vector<Vec3>& vertices, const std::vector<std::pair<int, int>>& edges, int pointsPerEdge);
std::vector<Vec3> generateShapePoints(Shape shape);
std::vector<Vec3> generateSpherePoints(int pointsPerSegment);
std::vector<Vec3> generateCylinderPoints(int pointsPerSegment);
std::vector<Vec3> generateConePoints(int pointsPerSegment);
std::vector<Vec3> createPyramid(float size, float height);
std::vector<std::pair<int, int>> createPyramidEdges();