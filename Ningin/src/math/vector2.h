#pragma once
#include <cmath>
#include <algorithm>
#include <string>
#include <iostream>

class Vector3;  // Forward declaration

class Vector2 {
public:
    float x, y;

    static const Vector2 UNIT_X;
    static const Vector2 UNIT_Y;
    static const Vector2 ZERO;
    static const Vector2 ONE;

    Vector2() : x(0), y(0) {}
    Vector2(float x, float y) : x(x), y(y) {}

    void abs(Vector2& out) const;
    void squareRoot(Vector2& out) const;
    void add(const Vector2& other, Vector2& out) const;
    float distance(const Vector2& other) const;
    float distanceSquared(const Vector2& other) const;
    float dot(const Vector2& other) const;
    float magnitude() const;
    float magnitudeSquared() const;

    static void max(const Vector2& v1, const Vector2& v2, Vector2& out);
    static void min(const Vector2& v1, const Vector2& v2, Vector2& out);
    static void clamp(const Vector2& vec_to_clamp, const Vector2& min, const Vector2& max, Vector2& out);

    // Operator overloads
    Vector2 operator-() const;
    Vector2 operator+(const Vector2& other) const;
    Vector2 operator-(const Vector2& other) const;
    Vector2 operator*(float a) const;
    Vector2 operator*(const Vector2& other) const;
    Vector2 operator/(const Vector2& other) const;
    Vector2 operator/(float a) const;

    bool operator==(const Vector2& other) const;
    bool operator!=(const Vector2& other) const;
    bool operator<(const Vector2& other) const;
    bool operator>(const Vector2& other) const;

    std::string toString() const;

    // Conversion from Vector3 to Vector2
    static Vector2 fromVector3(const Vector3& vec);
};
