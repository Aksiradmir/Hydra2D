#pragma once
#include "Particle.hpp"
#include "ParticleProperty.hpp"
#include "ParticleHolder.hpp"

#include <omp.h>
#include <span>

class ViscosityForce
{
protected:
    ParticleHolder* particle_holder;
    ParticleProperty* particle_property;
public:
    ViscosityForce(ParticleHolder& par_holder, ParticleProperty& par_property);
    ViscosityForce(ParticleHolder* par_holder, ParticleProperty* par_property);
    virtual ~ViscosityForce() {}
    virtual void calc_viscosity_forces(std::span<Vector2D> forces_span) {}
};



class MorrisLowViscosityForce : public ViscosityForce
{
private:
    double viscosity_coefficient;
public:
    MorrisLowViscosityForce(ParticleHolder& par_holder, ParticleProperty& par_property, double viscosity_coefficient);
    virtual ~MorrisLowViscosityForce() {}
    virtual void calc_viscosity_forces(std::span<Vector2D> forces_span);
};


