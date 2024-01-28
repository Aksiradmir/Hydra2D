#pragma once

#include <cmath>

struct Vector2D
{
    double x;
    double y;
    Vector2D() = default;
    Vector2D(double x, double y) : x(x), y(y) {}
    Vector2D& operator+= (const Vector2D& a);
};

Vector2D operator+ (const Vector2D& a, const Vector2D& b);

Vector2D operator- (const Vector2D& a, const Vector2D& b);

Vector2D operator* (const Vector2D& a, const double num);

Vector2D operator* (const double num, const Vector2D& a);

Vector2D operator/ (const Vector2D& a, const double num);

inline double dot(const Vector2D& a, const Vector2D& b) {return a.x * b.x + a.y * b.y;}
inline double abs(const Vector2D& a) {return sqrt(dot(a, a));}
