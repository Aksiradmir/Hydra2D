#include "ParticleHolder.hpp"

ParticleHolder::ParticleHolder(ParticleProperty& particle_property, int64_t number_of_particles) : particle_property(&particle_property), number_of_particles(number_of_particles)
{
    if (number_of_particles <= 0) {
        std::cerr << "Error: Number of particles must be greater than zero." << std::endl;
        std::exit(1);
    }
    
    particles.resize(number_of_particles);
}

double ParticleHolder::calc_speed_based_time_step()
{
    double max_speed = 0.0;
    for (auto &&particle : particles)
    {
        double speed = abs(particle.velocity);
        if (speed > max_speed) max_speed = speed;
    }
    if (max_speed > 0) return particle_property->get_smoothing_radius() / max_speed;
    else return 1e20;
}
