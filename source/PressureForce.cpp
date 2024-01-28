#include "PressureForce.hpp"

PressureForce::PressureForce(ParticleHolder &particle_holder, ParticleProperty &particle_property, PressureEOS &pressure) : particle_holder(&particle_holder), particle_property(&particle_property), pressure(&pressure)
{
    press_over_dens.resize(particle_holder.get_number_of_particles());
}

PressureForce::PressureForce(ParticleHolder *particle_holder, ParticleProperty *particle_property, PressureEOS *pressure) : particle_holder(particle_holder), particle_property(particle_property), pressure(pressure)
{
    press_over_dens.resize(particle_holder->get_number_of_particles());
}



void PressureForce::calc_pressure_forces(std::span<Vector2D> forces_span)
{
    update_press_over_dens();
    size_t number_of_particles = particle_holder->get_number_of_particles();
    #pragma omp parallel for 
    for (size_t i = 0; i < number_of_particles; i++)
    {
        for (size_t j = 0; j < number_of_particles; j++)
        {
            if (i != j) {
                forces_span[i] += particle_property->get_particle_mass() * (press_over_dens[i] + press_over_dens[j]) * particle_property->w_kernel_grad(particle_holder->get_particle(i).position, particle_holder->get_particle(j));
            }
        }
    }
}

void PressureForce::update_press_over_dens()
{
    size_t number_of_particles = particle_holder->get_number_of_particles();
    for (size_t i = 0; i < number_of_particles; i++) {
        press_over_dens[i] = pressure->evaluate(particle_holder->get_particle(i).density) / (particle_holder->get_particle(i).density * particle_holder->get_particle(i).density);
    }
}
