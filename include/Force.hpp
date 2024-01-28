#pragma once

#include "PressureForce.hpp"
#include "ViscosityForce.hpp"
#include "ExternalForce.hpp"
#include "Vector2D.hpp"
#include "ParticleHolder.hpp"
#include "ParticleProperty.hpp"

#include <span>
#include <vector>
#include <algorithm>

class Force
{
private:
    ParticleHolder* particle_holder;
    ParticleProperty* particle_property;
    std::vector<Vector2D> forces;
    PressureForce* pressure_force;
    ViscosityForce* viscosity_force;
    ExternalForce* external_force;
    bool if_calculated = false;
public:
    Force(ParticleHolder& particle_holder, ParticleProperty& particle_property, PressureForce& pressure_force, ViscosityForce& viscosity_force, ExternalForce& ext_force);
    Force(ParticleHolder* particle_holder, ParticleProperty* particle_property, PressureForce* pressure_force, ViscosityForce* viscosity_force, ExternalForce* ext_force);
    ~Force() {}
    void calc_forces();
    void apply_forces_to_particles(double dtime);
    inline Vector2D& get_force_over_particle(size_t i) {return forces[i];}
    double calc_force_based_time_step();
};


