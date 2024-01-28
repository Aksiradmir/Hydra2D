#include "PressureEOS.hpp"



LinearPressureEOS::LinearPressureEOS(double conversion_coeff, double target_density) : conversion_coeff(conversion_coeff), target_density(target_density)
{
    if (conversion_coeff<= 0.0) {
        std::cerr << "Error: Conversion coefficient in LinearPressureEOS must be greater than zero." << std::endl;
        std::exit(1);
    }

    if (target_density <= 0) {
        std::cerr << "Error: Target density in LinearPressureEOS must be greater than zero." << std::endl;
        std::exit(1);
    }
}

double LinearPressureEOS::evaluate(double density) const
{
    return conversion_coeff * (density - target_density);
}

WaterEOS::WaterEOS(double target_pressure, double target_density) : target_pressure(target_pressure), target_density(target_density)
{
    if (target_pressure <= 0.0) {
        std::cerr << "Error: Target pressure in WaterEOS must be greater than zero." << std::endl;
        std::exit(1);
    }

    if (target_density <= 0) {
        std::cerr << "Error: Target density in WaterEOS must be greater than zero." << std::endl;
        std::exit(1);
    }
}

double WaterEOS::evaluate(double density) const
{
    double dens_ratio = density / target_density;
    double dens_ratio_sq = dens_ratio * dens_ratio;
    return target_pressure * (dens_ratio_sq * dens_ratio_sq * dens_ratio_sq * dens_ratio - 1.0);
}
