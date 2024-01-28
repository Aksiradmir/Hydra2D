#pragma once

#include "Particle.hpp"
#include "ParticleProperty.hpp"
#include "ParticleHolder.hpp"

#include <span>
#include <omp.h>

class ExternalForce
{
protected:
    ParticleHolder* particle_holder;
    ParticleProperty* particle_property;
public:
    ExternalForce(ParticleHolder& par_holder, ParticleProperty& par_property);
    ExternalForce(ParticleHolder* par_holder, ParticleProperty* par_property);
    virtual ~ExternalForce() {}
    virtual void calc_external_forces(std::span<Vector2D> forces_span) {}
};



class ExternalGravityForce : public ExternalForce
{
private:
    double gravity_acceleration;
public:
    ExternalGravityForce(ParticleHolder& par_holder, ParticleProperty& par_property, double gravity_acceleration);
    virtual ~ExternalGravityForce () {}
    virtual void calc_external_forces(std::span<Vector2D> forces_span);
};


