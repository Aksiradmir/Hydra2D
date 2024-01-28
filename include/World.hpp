#pragma once

#include "Boundary.hpp"
#include "Particle.hpp"
#include "ParticleProperty.hpp"
#include "ParticleHolder.hpp"
#include "Force.hpp"
#include "DensityCalculator.hpp"
#include "ParticleWriter.hpp"

#include <vector>
#include <algorithm>
#include <omp.h>


class World
{
private:
    Boundary* boundary;
    ParticleHolder* particle_holder;
    ParticleProperty* particle_property;
    DensityCalculator* density_calculator;
    Force* force;
    ParticleWriter* writer;
    void update_particle_positionts(double dtime);

public:
    World(Boundary& boundary, ParticleHolder& paricle_holder, ParticleProperty& paricle_property, DensityCalculator& density_calculator, Force& force, ParticleWriter& particle_writer);
    World(Boundary* boundary, ParticleHolder* paricle_holder, ParticleProperty* paricle_property, DensityCalculator* density_calculator, Force* force, ParticleWriter* particle_writer);
    ~World() {}
    void update(const double t_start, const double t_stop);
};


