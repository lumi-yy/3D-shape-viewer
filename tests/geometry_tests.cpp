#include <gtest/gtest.h>

#include "geometry.hpp"

#include <cmath>

namespace {

float distanceFromOrigin(const Vec3& v) {
    return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

}  // namespace

TEST(Cube, HasEightVerticesAtGivenHalfSize) {
    auto vertices = createCube(2.0f);

    ASSERT_EQ(vertices.size(), 8u);
    for (const auto& v : vertices) {
        EXPECT_FLOAT_EQ(std::fabs(v.x), 2.0f);
        EXPECT_FLOAT_EQ(std::fabs(v.y), 2.0f);
        EXPECT_FLOAT_EQ(std::fabs(v.z), 2.0f);
    }
}

TEST(Cube, HasTwelveEdgesWithValidIndices) {
    auto vertices = createCube(1.0f);
    auto edges = createCubeEdges(vertices);

    EXPECT_EQ(edges.size(), 12u);
    for (const auto& e : edges) {
        EXPECT_GE(e.first, 0);
        EXPECT_LT(e.first, 8);
        EXPECT_GE(e.second, 0);
        EXPECT_LT(e.second, 8);
    }
}

TEST(Pyramid, HasFiveVerticesAndEightEdges) {
    auto vertices = createPyramid(6.0f, 6.0f);
    auto edges = createPyramidEdges();

    EXPECT_EQ(vertices.size(), 5u);
    EXPECT_EQ(edges.size(), 8u);
    for (const auto& e : edges) {
        EXPECT_LT(e.first, 5);
        EXPECT_LT(e.second, 5);
    }
}

TEST(Pyramid, ApexIsAboveTheBase) {
    auto vertices = createPyramid(6.0f, 6.0f);

    EXPECT_FLOAT_EQ(vertices[4].y, 3.0f);
    EXPECT_FLOAT_EQ(vertices[0].y, -3.0f);
}

TEST(GeneratePoints, ReturnsPointsPerEdgePlusOneForEachEdge) {
    std::vector<Vec3> vertices = {{0, 0, 0}, {1, 0, 0}};
    std::vector<std::pair<int, int>> edges = {{0, 1}};

    auto points = generatePoints(vertices, edges, 10);

    EXPECT_EQ(points.size(), 11u);
}

TEST(GeneratePoints, FirstAndLastPointsAreEdgeEndpoints) {
    std::vector<Vec3> vertices = {{0, 0, 0}, {2, 4, 6}};
    std::vector<std::pair<int, int>> edges = {{0, 1}};

    auto points = generatePoints(vertices, edges, 4);

    EXPECT_FLOAT_EQ(points.front().x, 0.0f);
    EXPECT_FLOAT_EQ(points.back().x, 2.0f);
    EXPECT_FLOAT_EQ(points.back().y, 4.0f);
    EXPECT_FLOAT_EQ(points.back().z, 6.0f);
}

TEST(Sphere, AllPointsLieOnTheSphereSurface) {
    auto points = generateSpherePoints(25);

    EXPECT_FALSE(points.empty());
    for (const auto& p : points) {
        EXPECT_NEAR(distanceFromOrigin(p), 4.0f, 1e-3f);  // radius is 4 in geometry.cpp
    }
}

TEST(Cylinder, PointsStayInsideTheCylinder) {
    auto points = generateCylinderPoints(15);

    EXPECT_FALSE(points.empty());
    for (const auto& p : points) {
        EXPECT_LE(std::fabs(p.y), 3.0f + 1e-4f);
        EXPECT_LE(std::sqrt(p.x * p.x + p.z * p.z), 2.5f + 1e-4f);
    }
}

TEST(Cone, PointsStayInsideTheCone) {
    auto points = generateConePoints(15);

    EXPECT_FALSE(points.empty());
    for (const auto& p : points) {
        EXPECT_GE(p.y, -3.0f - 1e-4f);
        EXPECT_LE(p.y, 3.0f + 1e-4f);

        // the radius shrinks linearly from 2.5 at the base to 0 at the apex
        float maxRadius = 2.5f * (3.0f - p.y) / 6.0f;
        EXPECT_LE(std::sqrt(p.x * p.x + p.z * p.z), maxRadius + 1e-3f);
    }
}

TEST(GenerateShapePoints, EveryShapeProducesPoints) {
    for (Shape s : {Shape::Cube, Shape::Sphere, Shape::Cylinder, Shape::Cone, Shape::Pyramid}) {
        EXPECT_FALSE(generateShapePoints(s).empty());
    }
}

TEST(GenerateShapePoints, ExitProducesNoPoints) {
    EXPECT_TRUE(generateShapePoints(Shape::Exit).empty());
}