#include "geometry.hpp"
#include "command.hpp"

#include <utility>
#include <cmath>

std::vector<Vec3> createCube(float halfSize){
    std::vector<Vec3> res;

    for (int x : {-1, 1}) {
        for (int y : {-1, 1}) {
            for (int z : {-1, 1}) {
                res.push_back({x * halfSize, y * halfSize, z * halfSize});
            }
        }
    }

    return res;
}

std::vector<std::pair<int, int>> createCubeEdges(const std::vector<Vec3>& vertices){
    
    std::vector<std::pair<int, int>> edges;

    for (int i = 0; i < 8; i++) {
        for (int j = i + 1; j < 8; j++) {
            int diff = 0;

            if (vertices[i].x != vertices[j].x) diff++;
            if (vertices[i].y != vertices[j].y) diff++;
            if (vertices[i].z != vertices[j].z) diff++;

            if (diff == 1) {
                edges.push_back({i, j});
            }
        }
    }

    return edges;
}

std::vector<Vec3> generatePoints(const std::vector<Vec3>& vertices, const std::vector<std::pair<int, int>>& edges, int pointsPerEdge){
    std::vector<Vec3> points;

    for (const auto& edge : edges) {
        Vec3 a = vertices[edge.first];
        Vec3 b = vertices[edge.second];

        for (int i = 0; i <= pointsPerEdge; i++) {
            float t = static_cast<float>(i) / pointsPerEdge;

            points.push_back(a + (b - a) * t);
        }
    }

    return points;
}

std::vector<Vec3> generateSpherePoints(int pointsPerSegment) {
    std::vector<Vec3> points;

    const float radius = 4.0f;

    for (int i = 0; i <= pointsPerSegment; i++) {
        float angle = PI * static_cast<float>(i) / pointsPerSegment;

        float y = radius * cosf(angle);
        float ringRadius = radius * sinf(angle);

        for (int j = 0; j < (pointsPerSegment * 2); j++) {
            float theta = 2.0f * PI * static_cast<float>(j) / (pointsPerSegment * 2);

            float x = ringRadius * cosf(theta);
            float z = ringRadius * sinf(theta);

            points.push_back({x, y, z});
        }
    }

    return points;
}

std::vector<Vec3> generateCylinderPoints(int pointsPerSegment) {
    std::vector<Vec3> points;
    const float radius = 5.0f;

    for (int i = 0; i <= pointsPerSegment; i++) {
        float y = -3.0f + 6.0f * static_cast<float>(i) / pointsPerSegment;

        for (int j = 0; j < pointsPerSegment; j++) {
            float theta = 2.0f * PI * j / pointsPerSegment;

            float x = (radius / 2.0f) * cosf(theta);
            float z = (radius / 2.0f) * sinf(theta);

            points.push_back({x, y, z});
        }
    }

    for (int i = 0; i < 2; i++) {
        float y = (i == 0) ? 3.0f : -3.0f;

        for (int r = 1; r <= pointsPerSegment / 3; r++) {
            float ringRadius = (radius / 2.0f) * r / (pointsPerSegment / 3);

            for (int j = 0; j < pointsPerSegment; j++) {
                float theta = 2.0f * PI * j / pointsPerSegment;

                float x = ringRadius * cosf(theta);
                float z = ringRadius * sinf(theta);

                points.push_back({x, y, z});
            }
        }

        points.push_back({0.0f, y, 0.0f});
    }

    for (int i = 0; i < 5; i++) {
        float y = -3.0f + 6.0f * i / 4.0f;

        for (int j = 0; j < pointsPerSegment * 2; j++) {
            float theta = 2.0f * PI * j / (pointsPerSegment * 2);

            float x = (radius / 2.0f) * cosf(theta);
            float z = (radius / 2.0f) * sinf(theta);

            points.push_back({x, y, z});
        }
    }

    return points;
}

std::vector<Vec3> generateConePoints(int pointsPerSegment){
    std::vector<Vec3> points;

    const float radius = 5.0f;
    const float height = 6.0f;
    const int segments = pointsPerSegment / 3;

    for (int r = 1; r <= segments; r++) {
    float ringRadius = (radius / 2.0f) * r / segments;
    float y = -3.0f;

    int count = (r == segments) ? pointsPerSegment * 2 : pointsPerSegment;

    for (int j = 0; j < count; j++) {
        float theta = 2.0f * PI * j / count;

        float x = ringRadius * cosf(theta);
        float z = ringRadius * sinf(theta);

        points.push_back({x, y, z});
    }
}

    for (int j = 0; j < pointsPerSegment; j++) {
        float theta = 2.0f * PI * j / pointsPerSegment;

        float baseX = (radius / 2.0f) * cosf(theta);
        float baseZ = (radius / 2.0f) * sinf(theta);

        for (int i = 0; i <= pointsPerSegment; i++) {
            float t = static_cast<float>(i) / pointsPerSegment;

            float x = baseX * (1.0f - t);
            float y = -3.0f + height * t;
            float z = baseZ * (1.0f - t);

            points.push_back({x, y, z});
        }
    }

    return points;
}

std::vector<Vec3> createPyramid(float size, float height) {
    float half = size / 2.0f;

    return {
        {-half, -height / 2.0f, -half},
        { half, -height / 2.0f, -half},
        {-half, -height / 2.0f,  half},
        { half, -height / 2.0f,  half},
        {0.0f,   height / 2.0f, 0.0f}
    };
}

std::vector<std::pair<int, int>> createPyramidEdges() {
    return {
        {0, 1}, {1, 3}, {3, 2}, {2, 0},
        {0, 4}, {1, 4}, {2, 4}, {3, 4}
    };
}

std::vector<Vec3> generateShapePoints(Shape shape) {
    switch (shape) {
        case Shape::Cube: {
            auto vertices = createCube(2.0f);
            auto edges = createCubeEdges(vertices);
            return generatePoints(vertices, edges, 25);
        }

        case Shape::Sphere:
            return generateSpherePoints(25);

        case Shape::Cylinder:
            return generateCylinderPoints(15);

        case Shape::Cone:
            return generateConePoints(15);

        case Shape::Pyramid: {
            auto vertices = createPyramid(6.0f, 6.0f);
            auto edges = createPyramidEdges();
            return generatePoints(vertices, edges, 25);
        }

        case Shape::Exit:
            break;
    }

    return {};
}
