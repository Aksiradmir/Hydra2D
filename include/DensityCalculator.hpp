#pragma once

#include "Particle.hpp"
#include "ParticleProperty.hpp"
#include "ParticleHolder.hpp"

#include <omp.h>

class DensityCalculator
{
public:
    DensityCalculator() {}
    virtual ~DensityCalculator() {}
    virtual double calc_density_in_point(const Vector2D& point) const = 0;
    virtual void update_densities() const = 0;
};

class ClassicDensityCalculator : public DensityCalculator
{
private:
    ParticleHolder* particle_holder;
    ParticleProperty* particle_property;
public:
    ClassicDensityCalculator(ParticleHolder& par_holder, ParticleProperty& par_property);
    ClassicDensityCalculator(ParticleHolder* par_holder, ParticleProperty* par_property);
    virtual ~ClassicDensityCalculator() {}
    virtual double calc_density_in_point(const Vector2D& point) const;
    virtual void update_densities() const;
};




