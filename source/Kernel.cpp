#include "Kernel.hpp"

double CubicKernel::kernel_function(double x) const
{
    constexpr double inv_volume = 10.0 / (7.0 * 3.14159265359);
    if (x < 1.0) return (1.0 - 1.5 * x * x + 0.75 * x * x * x) * inv_volume;
    else if (x < 2.0) return inv_volume * 0.25 * (2.0 - x) * (2.0 - x) * (2.0 - x);
    else return 0.0;
}

double CubicKernel::kernel_function_derivative(double x) const
{
    constexpr double inv_volume = 10.0 / (7.0 * 3.14159265359);
    if (x < 1.0) return ( - 3.0 * x + 2.25 * x * x) * inv_volume;
    else if (x < 2.0) return inv_volume * 0.5 * (2.0 - x) * (x - 2.0);
    return 0.0;
}



double CubicKernelSpiky::kernel_function(double x) const
{
    constexpr double inv_volume = 10.0 / 3.14159265359;
    double val = 1.0 - x;
    if (x < 1.0) return val * val * val * inv_volume;
    return 0.0;
}

double CubicKernelSpiky::kernel_function_derivative(double x) const
{
    constexpr double neg_inv_volume_triple = -10.0 / 3.14159265359 * 3;
    double val = 1.0 - x;
    if (x < 1.0) return val * val * neg_inv_volume_triple;
    return 0.0;
}




double CubicKernelViscosity::kernel_function(double x) const
{

    return 0.0;
}

double CubicKernelViscosity::kernel_function_derivative(double x) const
{
    return 0.0;
}





double SextaKernel::kernel_function(double x) const
{
    constexpr double inv_volume = 4.0 / 3.14159265359;
    double val = 1.0 - x * x;
    if (x < 1.0) return val * val * val * inv_volume;
    return 0.0;
}

double SextaKernel::kernel_function_derivative(double x) const
{
    constexpr double neg_inv_volume_triple = - 4.0 / 3.14159265359 * 6;
    double val = 1.0 - x * x;
    if (x < 1.0) return val * val * x * neg_inv_volume_triple;
    return 0.0;
}
