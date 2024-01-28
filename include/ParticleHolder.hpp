#pragma once

#include "Particle.hpp"
#include "ParticleProperty.hpp"

#include <vector>
#include <iostream>


class ParticleHolder
{
private:
    std::vector<Particle> particles;
    ParticleProperty* particle_property;
    size_t number_of_particles;
public:
    ParticleHolder(ParticleProperty& particle_property, int64_t number_of_particles);
    ~ParticleHolder() {}
    inline Particle& get_particle(size_t i) {return particles[i];}
    inline size_t get_number_of_particles() const {return number_of_particles;}
    double calc_speed_based_time_step();
};