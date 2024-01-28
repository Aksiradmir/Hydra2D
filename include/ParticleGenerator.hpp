#pragma once
#include "Particle.hpp"
#include "Box.hpp"
#include "ParticleHolder.hpp"

#include <random>

class ParticleGenerator
{
public:
    ParticleGenerator() {}
    virtual ~ParticleGenerator() {}
    virtual void generate_particles(ParticleHolder& particle_holder) const = 0;
};



class BoxShapeRandomParticleGenerator 
{
private:
    Box* box;
    double particle_mass;
public:
    BoxShapeRandomParticleGenerator (Box& box);
    virtual ~BoxShapeRandomParticleGenerator () {}
    virtual void generate_particles(ParticleHolder& particle_holder);
};


