#include "Box.hpp"

Box::Box(const double x_min, const double x_max, const double y_min, const double y_max) : x_min(x_min), x_max(x_max), y_min(y_min), y_max(y_max)
{
    if (x_min > x_max) {
        std::cerr << "Error: x_max must be greater than x_min in Box." << std::endl;
        std::exit(1);
    }
    if (y_min > y_max) {
        std::cerr << "Error: y_max must be greater than y_min in Box." << std::endl;
        std::exit(1);
    }
}

bool Box::is_inside(Vector2D &point) const
{
    return not(point.x < x_min or point.x > x_max or point.y < y_min or point.y > y_max);
}
