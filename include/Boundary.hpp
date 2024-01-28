#pragma once
#include "Box.hpp"

#include <vector>

class Boundary
{
public:
    Boundary() {}
    virtual ~Boundary() {}
    virtual bool check_out_of_bounds(Vector2D& point) const = 0;
    virtual void apply_boundary_condition(Particle& particle, Vector2D& assumed_new_position) const = 0;
};


class ReflectiveRectangularBoundary : public Boundary
{
private:
    Box* box;
    double reflection_coefficient;
public:
    ReflectiveRectangularBoundary(Box& box, const double reflection_coefficient);
    virtual ~ReflectiveRectangularBoundary() {}
    virtual bool check_out_of_bounds(Vector2D& point) const;
    virtual void apply_boundary_condition(Particle& particle, Vector2D& assumed_new_position) const;
};


