#include "Boundary.hpp"


ReflectiveRectangularBoundary::ReflectiveRectangularBoundary(Box &box, const double reflection_coefficient) : box(&box), reflection_coefficient(reflection_coefficient)
{
    if (reflection_coefficient <= 0) {
        std::cerr << "Error: Reflection coefficient in ReflectiveRectangularBoundary must be greater than zero." << std::endl;
        std::exit(1);
    }
}

bool ReflectiveRectangularBoundary::check_out_of_bounds(Vector2D &point) const
{
    return not(box->is_inside(point));
}

void ReflectiveRectangularBoundary::apply_boundary_condition(Particle &particle, Vector2D &assumed_new_position) const
{
    if (assumed_new_position.x < box->get_xmin()){
        double dx = box->get_xmin() - assumed_new_position.x;
        assumed_new_position.x = box->get_xmin() + dx * reflection_coefficient;
        particle.velocity.x *= -1.0 * reflection_coefficient;
    }
    if (assumed_new_position.x > box->get_xmax()){
        double dx = assumed_new_position.x - box->get_xmax();
        assumed_new_position.x = box->get_xmax() - dx * reflection_coefficient;
        particle.velocity.x *= -1.0 * reflection_coefficient;
    }

    if (assumed_new_position.y < box->get_ymin()){
        double dy = box->get_ymin() - assumed_new_position.y;
        assumed_new_position.y = box->get_ymin() + dy * reflection_coefficient;
        particle.velocity.y *= -1.0 * reflection_coefficient;
    }
    if (assumed_new_position.y > box->get_ymax()){
        double dy = assumed_new_position.y - box->get_ymax();
        assumed_new_position.y = box->get_ymax() - dy * reflection_coefficient;
        particle.velocity.y *= -1.0 * reflection_coefficient;
    } 
}
