#include <gtest/gtest.h>

#include "renderer.hpp"

#include <cmath>

namespace {

constexpr float kPi = 3.14159265358979f;

float length(const Vec3& v) {
    return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

void expectVecNear(const Vec3& a, const Vec3& b, float eps = 1e-5f) {
    EXPECT_NEAR(a.x, b.x, eps);
    EXPECT_NEAR(a.y, b.y, eps);
    EXPECT_NEAR(a.z, b.z, eps);
}

}  // namespace

TEST(RotateY, ZeroAngleChangesNothing) {
    expectVecNear(rotateY({1, 2, 3}, 0.0f), {1, 2, 3});
}

TEST(RotateY, QuarterTurnMovesXAxisToZAxis) {
    expectVecNear(rotateY({1, 0, 0}, kPi / 2), {0, 0, 1});
}

TEST(RotateY, KeepsYCoordinate) {
    EXPECT_NEAR(rotateY({1, 2, 3}, 0.7f).y, 2.0f, 1e-6f);
}

TEST(RotateY, FullTurnReturnsOriginalPoint) {
    expectVecNear(rotateY({1, 2, 3}, 2 * kPi), {1, 2, 3}, 1e-4f);
}

TEST(RotateY, PreservesLength) {
    Vec3 v{1, 2, 3};
    EXPECT_NEAR(length(rotateY(v, 1.234f)), length(v), 1e-5f);
}

TEST(RotateX, ZeroAngleChangesNothing) {
    expectVecNear(rotateX({1, 2, 3}, 0.0f), {1, 2, 3});
}

TEST(RotateX, QuarterTurnMovesYAxisToZAxis) {
    expectVecNear(rotateX({0, 1, 0}, kPi / 2), {0, 0, 1});
}

TEST(RotateX, KeepsXCoordinate) {
    EXPECT_NEAR(rotateX({1, 2, 3}, 0.7f).x, 1.0f, 1e-6f);
}

TEST(RotateX, FullTurnReturnsOriginalPoint) {
    expectVecNear(rotateX({1, 2, 3}, 2 * kPi), {1, 2, 3}, 1e-4f);
}

TEST(RotateX, PreservesLength) {
    Vec3 v{1, 2, 3};
    EXPECT_NEAR(length(rotateX(v, -0.4f)), length(v), 1e-5f);
}