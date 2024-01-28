#include "ParticleProperty.hpp"

ParticleProperty::ParticleProperty(double smoothing_radius, double mass, Kernel &wkernel) : smoothing_radius(smoothing_radius), mass(mass), kernel(&wkernel)
{
    if (smoothing_radius <= 0) {
        std::cerr << "Error: Smoothing radius of particles must be greater than zero." << std::endl;
        std::exit(1);
    }
    if (mass <= 0) {
        std::cerr << "Error: Mass of particles must be greater than zero." << std::endl;
        std::exit(1);
    }
}

double ParticleProperty::w_kernel(const Vector2D &point, const Particle &particle) const
{
    double dist = abs(point - particle.position) / smoothing_radius;
    return kernel->kernel_function(dist) / (smoothing_radius * smoothing_radius);
}
Vector2D ParticleProperty::w_kernel_grad(const Vector2D& point, const Particle& particle) const {
    double dist = abs(point - particle.position) / smoothing_radius;
    Vector2D norm_vector = (particle.position - point) / dist;
    double grad_abs = kernel->kernel_function_derivative(dist) / (smoothing_radius * smoothing_radius * smoothing_radius);
    return norm_vector * grad_abs;
}

double ParticleProperty::w_kernel_deriv_div_over_dist(const Vector2D &point, const Particle &particle) const
{
    double dist = abs(point - particle.position) / smoothing_radius;
    double grad_abs = kernel->kernel_function_derivative(dist) / (smoothing_radius * smoothing_radius * smoothing_radius);
    return grad_abs / dist;
}
