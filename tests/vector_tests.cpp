#include <gtest/gtest.h>

#include "vector.hpp"

namespace {

void expectVecEq(const Vec3& a, const Vec3& b) {
    EXPECT_FLOAT_EQ(a.x, b.x);
    EXPECT_FLOAT_EQ(a.y, b.y);
    EXPECT_FLOAT_EQ(a.z, b.z);
}

}  // namespace

TEST(Vec3, Addition) {
    expectVecEq(Vec3{1, 2, 3} + Vec3{4, 5, 6}, Vec3{5, 7, 9});
}

TEST(Vec3, AdditionWithZeroVectorChangesNothing) {
    expectVecEq(Vec3{1, -2, 3} + Vec3{0, 0, 0}, Vec3{1, -2, 3});
}

TEST(Vec3, Subtraction) {
    expectVecEq(Vec3{5, 7, 9} - Vec3{4, 5, 6}, Vec3{1, 2, 3});
}

TEST(Vec3, SubtractingVectorFromItselfGivesZero) {
    expectVecEq(Vec3{3, -1, 2} - Vec3{3, -1, 2}, Vec3{0, 0, 0});
}

TEST(Vec3, ScalarMultiplication) {
    expectVecEq(Vec3{1, -2, 3} * 2.0f, Vec3{2, -4, 6});
}

TEST(Vec3, MultiplicationByZeroGivesZeroVector) {
    expectVecEq(Vec3{1, -2, 3} * 0.0f, Vec3{0, 0, 0});
}

TEST(Vec3, MultiplicationByNegativeScalarFlipsDirection) {
    expectVecEq(Vec3{1, -2, 3} * -1.0f, Vec3{-1, 2, -3});
}