#pragma once
#include "Vector2D.hpp"
#include "Kernel.hpp"
#include "Particle.hpp"

#include <iostream>

class ParticleProperty
{
private:
    double smoothing_radius;
    double mass;
    Kernel* kernel;

public:
    ParticleProperty(double smoothing_radius, double mass, Kernel& wkernel);
    ~ParticleProperty() {}
    double w_kernel(const Vector2D& point, const Particle& particle) const;
    Vector2D w_kernel_grad(const Vector2D& point, const Particle& particle) const;
    double w_kernel_deriv_div_over_dist(const Vector2D& point, const Particle& particle) const;
    inline double get_smoothing_radius() const {return smoothing_radius;}
    inline double get_particle_mass() const {return mass;}
};