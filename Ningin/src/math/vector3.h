#pragma once

#include <iostream>
#include <cmath>

class Vector2;

class Vector3 {
public:
    float x, y, z;

    static const Vector3 UNIT_X;
    static const Vector3 UNIT_Y;
    static const Vector3 UNIT_Z;
    static const Vector3 ZERO;
    static const Vector3 ONE;

    // Constructors
    Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f);
    Vector3(const Vector2& vec);

    // Methods
    void abs(Vector3& out) const;
    void squareRoot(Vector3& out) const;
    void add(const Vector3& other, Vector3& out) const;
    float distance(const Vector3& other) const;
    float distanceSquared(const Vector3& other) const;
    float dot(const Vector3& other) const;
    float magnitude() const;
    float magnitudeSquared() const;

    static void max(const Vector3& v1, const Vector3& v2, Vector3& out);
    static void min(const Vector3& v1, const Vector3& v2, Vector3& out);
    static void clamp(const Vector3& toClamp, const Vector3& min, const Vector3& max, Vector3& out);

    // Operator Overloads
    Vector3 operator-() const;
    Vector3 operator+(const Vector3& other) const;
    Vector3 operator-(const Vector3& other) const;
    Vector3 operator*(float a) const;
    Vector3 operator*(const Vector3& other) const;
    Vector3 operator/(float a) const;
    Vector3 operator/(const Vector3& other) const;

    bool operator==(const Vector3& other) const;
    bool operator!=(const Vector3& other) const;
    bool operator<(const Vector3& other) const;
    bool operator<=(const Vector3& other) const;
    bool operator>(const Vector3& other) const;
    bool operator>=(const Vector3& other) const;

    // Debugging
    friend std::ostream& operator<<(std::ostream& os, const Vector3& vec);
};
