#include "World.hpp"

void World::update_particle_positionts(double dtime)
{
    size_t number_of_particles = particle_holder->get_number_of_particles();
    #pragma omp parallel for num_threads(8)
    for (size_t i = 0; i < number_of_particles; i++)
    {
        Vector2D assumed_new_position = particle_holder->get_particle(i).position + particle_holder->get_particle(i).velocity * dtime;
        boundary->apply_boundary_condition(particle_holder->get_particle(i), assumed_new_position);
        particle_holder->get_particle(i).position = assumed_new_position;
    } 
}

World::World(Boundary &boundary, ParticleHolder &paricle_holder, ParticleProperty &paricle_property, DensityCalculator &density_calculator, 
            Force &force, ParticleWriter &particle_writer) : boundary(&boundary), particle_holder(&paricle_holder), density_calculator(&density_calculator),
            force(&force), writer(&particle_writer)
{
}

World::World(Boundary *boundary, ParticleHolder *paricle_holder, ParticleProperty *paricle_property, DensityCalculator *density_calculator, 
            Force *force, ParticleWriter *particle_writer): boundary(boundary), particle_holder(paricle_holder), density_calculator(density_calculator),
            force(force), writer(particle_writer)
{
}

void World::update(const double t_start, const double t_stop)
{
    if (t_stop < t_start) {
        std::cerr << "Error: Start time must be less than stop time in World::update()." << std::endl;
        std::exit(1);
    }

    double time = t_start;
    density_calculator->update_densities();
    force->calc_forces();
    double time_step = 0.25 * force->calc_force_based_time_step();
    force->apply_forces_to_particles(0.5 * time_step);
    writer->write(time);
    size_t time_steps_with_const_steps = 0;
    while (time < t_stop){
        this->update_particle_positionts(time_step);
        density_calculator->update_densities();
        force->apply_forces_to_particles(time_step);
        time += time_step;
        writer->write(time);
        time_steps_with_const_steps++;
        if (time_steps_with_const_steps == 4){
            time_step = 0.25 * std::min(force->calc_force_based_time_step(), particle_holder->calc_speed_based_time_step());
            time_steps_with_const_steps = 0;
        }
    }
}