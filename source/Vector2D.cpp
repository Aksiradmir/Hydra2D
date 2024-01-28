#include "Vector2D.hpp"

Vector2D operator+ (const Vector2D& a, const Vector2D& b){
    Vector2D c;
    c.x = a.x + b.x;
    c.y = a.y + b.y;
    return c;
}

Vector2D operator- (const Vector2D& a, const Vector2D& b){
    Vector2D c;
    c.x = a.x - b.x;
    c.y = a.y - b.y;
    return c;
}

Vector2D operator* (const Vector2D& a, const double num){
    Vector2D c;
    c.x = a.x * num;
    c.y = a.y * num;
    return c;
}

Vector2D operator* (const double num, const Vector2D& a){
    Vector2D c;
    c.x = a.x * num;
    c.y = a.y * num;
    return c;
}

Vector2D operator/ (const Vector2D &a, const double num){
    Vector2D c;
    c.x = a.x / num;
    c.y = a.y / num;
    return c;
}

Vector2D &Vector2D::operator+=(const Vector2D &a)
{
    this->x += a.x;
    this->y += a.y;
    return *this;
}




