#include "vector.hpp"

Vec3 operator+(const Vec3& a, const Vec3& b) {
    return {
        a.x + b.x,
        a.y + b.y,
        a.z + b.z
    };
}

Vec3 operator-(const Vec3& a, const Vec3& b) {
    return {
        a.x - b.x,
        a.y - b.y,
        a.z - b.z
    };
}

Vec3 operator*(const Vec3& v, float scalar) {
    return {
        v.x * scalar,
        v.y * scalar,
        v.z * scalar
    };
}