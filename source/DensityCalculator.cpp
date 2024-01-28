#include "DensityCalculator.hpp"

#include <iostream>

ClassicDensityCalculator::ClassicDensityCalculator(ParticleHolder &par_holder, ParticleProperty &par_property) : particle_holder(&par_holder), particle_property(&par_property)
{
}

ClassicDensityCalculator::ClassicDensityCalculator(ParticleHolder *par_holder, ParticleProperty *par_property) : particle_holder(par_holder), particle_property(par_property)
{
}

double ClassicDensityCalculator::calc_density_in_point(const Vector2D &point) const
{
    double density = 0.0;
    size_t number_of_particles = particle_holder->get_number_of_particles();
    for (size_t j = 0; j < number_of_particles; j++)
    {
        density += particle_property->get_particle_mass() * particle_property->w_kernel(point, particle_holder->get_particle(j));
    }
    return density;
}

void ClassicDensityCalculator::update_densities() const
{
    size_t number_of_particles = particle_holder->get_number_of_particles();

    #pragma omp parallel for
    for (size_t i = 0; i < number_of_particles; i++)
    {
        particle_holder->get_particle(i).density = 0.0;
        for (size_t j = 0; j < number_of_particles; j++)
        {
            particle_holder->get_particle(i).density += particle_property->get_particle_mass() * particle_property->w_kernel(particle_holder->get_particle(i).position, particle_holder->get_particle(j));
        }
    }
}
