#pragma once

#include "Vector2D.hpp"



struct Particle
{
    Vector2D position;
    Vector2D velocity;
    double density;
    Particle() = default;
    Particle(const Vector2D& pos, const Vector2D& vel); 
};





