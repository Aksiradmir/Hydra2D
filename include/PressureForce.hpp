#pragma once
#include "PressureEOS.hpp"
#include "Particle.hpp"
#include "ParticleProperty.hpp"
#include "ParticleHolder.hpp"

#include <omp.h>
#include <span>

class PressureForce
{
private:
    ParticleHolder* particle_holder;
    ParticleProperty* particle_property;
    PressureEOS* pressure;
    std::vector<double> press_over_dens;
    void update_press_over_dens();
public:
    PressureForce(ParticleHolder& particle_holder, ParticleProperty& particle_property, PressureEOS& pressure);
    PressureForce(ParticleHolder* particle_holder, ParticleProperty* particle_property, PressureEOS* pressure);
    ~PressureForce() {}
    void calc_pressure_forces(std::span<Vector2D> forces_span);
};


