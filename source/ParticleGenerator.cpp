#include "ParticleGenerator.hpp"


BoxShapeRandomParticleGenerator::BoxShapeRandomParticleGenerator(Box &box) : box(&box)
{
}

void BoxShapeRandomParticleGenerator::generate_particles(ParticleHolder &particle_holder)
{
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_real_distribution<> dis_x(box->get_xmin(), box->get_xmax());
    std::uniform_real_distribution<> dis_y(box->get_ymin(), box->get_ymax());
    size_t number_of_particles = particle_holder.get_number_of_particles();
    for (size_t i = 0; i < number_of_particles; i++)
    {
        particle_holder.get_particle(i).position.x = dis_x(gen);
        particle_holder.get_particle(i).position.y = dis_y(gen);
    }
}