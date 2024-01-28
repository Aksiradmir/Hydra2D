#pragma once
#include "Vector2D.hpp"

class Shape
{
public:
    Shape() {}
    virtual ~Shape() {}
    virtual bool is_inside(Vector2D &point) const = 0;
};


