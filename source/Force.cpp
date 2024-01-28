#include "Force.hpp"

Force::Force(ParticleHolder &particle_holder, ParticleProperty& particle_property, PressureForce &pressure_force, ViscosityForce &viscosity_force, 
             ExternalForce &ext_force) : particle_holder(&particle_holder), particle_property(&particle_property), pressure_force(&pressure_force), viscosity_force(&viscosity_force), external_force(&ext_force)

{
    forces.resize(particle_holder.get_number_of_particles());
}

Force::Force(ParticleHolder *particle_holder, ParticleProperty* particle_property, PressureForce *pressure_force, ViscosityForce *viscosity_force, 
             ExternalForce *ext_force) : particle_holder(particle_holder), particle_property(particle_property), pressure_force(pressure_force), viscosity_force(viscosity_force), external_force(ext_force)
{
    forces.resize(particle_holder->get_number_of_particles());
}

void Force::calc_forces()
{
    if (!(if_calculated)) {
        for (auto &&f_vec : forces){
            f_vec = Vector2D();
        }
        auto vec_span = std::span(forces);
        pressure_force->calc_pressure_forces(vec_span);
        viscosity_force->calc_viscosity_forces(vec_span);
        external_force->calc_external_forces(vec_span);
        if_calculated = true;
    }
}

void Force::apply_forces_to_particles(double dtime)
{
    this->calc_forces();
    size_t number_of_particles = particle_holder->get_number_of_particles();
    for (size_t i = 0; i < number_of_particles; i++)
    {
        particle_holder->get_particle(i).velocity += forces[i] * dtime;
    }
    if_calculated = false;
}

double Force::calc_force_based_time_step()
{
    double max_force = 0.0;
    size_t number_of_particles = particle_holder->get_number_of_particles();
    for (size_t i = 0; i < number_of_particles; i++)
    {
        double force = abs(forces[i]);
        if (force > max_force) max_force = force;
    }
    if (max_force > 0.0) return std::sqrt(particle_property->get_smoothing_radius() / max_force);
    else return 1e20;
}
