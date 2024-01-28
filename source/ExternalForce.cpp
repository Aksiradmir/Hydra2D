#include "ExternalForce.hpp"

ExternalForce::ExternalForce(ParticleHolder &par_holder, ParticleProperty &par_property) : particle_holder(&par_holder), particle_property(&par_property)
{
}

ExternalForce::ExternalForce(ParticleHolder *par_holder, ParticleProperty *par_property) : particle_holder(par_holder), particle_property(par_property)
{
}

ExternalGravityForce::ExternalGravityForce(ParticleHolder &par_holder, ParticleProperty &par_property, double gravity_acceleration) : ExternalForce(par_holder, par_property), gravity_acceleration(gravity_acceleration)
{
}

void ExternalGravityForce::calc_external_forces(std::span<Vector2D> forces_span)
{
    size_t number_of_particles = particle_holder->get_number_of_particles();
    for (size_t i = 0; i < number_of_particles; i++)
    {
        forces_span[i].y += -gravity_acceleration;
    }
}
