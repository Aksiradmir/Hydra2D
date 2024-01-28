#include "ViscosityForce.hpp"

ViscosityForce::ViscosityForce(ParticleHolder &par_holder, ParticleProperty &par_property) : particle_holder(&par_holder), particle_property(&par_property)
{
}

ViscosityForce::ViscosityForce(ParticleHolder *par_holder, ParticleProperty *par_property) : particle_holder(par_holder), particle_property(par_property)
{
}

MorrisLowViscosityForce::MorrisLowViscosityForce(ParticleHolder &par_holder, ParticleProperty &par_property, double viscosity_coefficient) : ViscosityForce(par_holder, par_property), viscosity_coefficient(viscosity_coefficient)
{
    if (viscosity_coefficient <= 0.0) {
        std::cerr << "Error: Viscosity coefficient must be greater then zero." << std::endl;
        std::exit(1);
    }
}

void MorrisLowViscosityForce::calc_viscosity_forces(std::span<Vector2D> forces_span)
{
    size_t number_of_particles = particle_holder->get_number_of_particles();
    #pragma omp parallel for 
    for (size_t i = 0; i < number_of_particles; i++)
    {
        for (size_t j = 0; j < number_of_particles; j++)
        {
            if (i != j) {
                double dens_i = particle_holder->get_particle(i).density;
                double dens_j = particle_holder->get_particle(j).density;
                double linear_viscos_coeff = viscosity_coefficient * particle_property->get_particle_mass() * (dens_i + dens_j) / (dens_i * dens_j);
                linear_viscos_coeff *= particle_property->w_kernel_deriv_div_over_dist(particle_holder->get_particle(i).position, particle_holder->get_particle(j));
                forces_span[i] += linear_viscos_coeff * (particle_holder->get_particle(i).velocity - particle_holder->get_particle(j).velocity);
            }
        }
    } 
}
