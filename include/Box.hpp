#pragma once
#include "Vector2D.hpp"
#include "Particle.hpp"
#include "Shape.hpp"

#include <iostream>

class Box : public Shape
{
private:
    double x_min;
    double x_max;
    double y_min;
    double y_max;
public:
    Box(const double x_min, const double x_max, const double y_min, const double y_max);
    virtual ~Box() {}
    virtual bool is_inside(Vector2D &point) const;
    inline double get_xmin() const {return x_min;}
    inline double get_xmax() const {return x_max;}
    inline double get_ymin() const {return y_min;}
    inline double get_ymax() const {return y_max;}
};


