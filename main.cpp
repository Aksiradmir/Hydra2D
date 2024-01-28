
#include "Boundary.hpp"
#include "Particle.hpp"
#include "ParticleProperty.hpp"
#include "ParticleHolder.hpp"
#include "ParticleGenerator.hpp"
#include "Force.hpp"
#include "DensityCalculator.hpp"
#include "ParticleWriter.hpp"
#include "Box.hpp"
#include "Kernel.hpp"
#include "PressureEOS.hpp"
#include "World.hpp"

#include <string>
#include <filesystem>
#include <omp.h>
#include <chrono>

namespace fs = std::filesystem;

int main(int argc, char const *argv[])
{
    // Particle initialization
    auto kernel = CubicKernelSpiky();
    auto part_prop = ParticleProperty(0.3, 1.0, kernel);
    auto part_holder = ParticleHolder(part_prop, 2000);
    auto part_generation_box = Box(3, 8, 4, 7);
    auto part_generator = BoxShapeRandomParticleGenerator(part_generation_box);
    part_generator.generate_particles(part_holder);

    // Forces initialization
    auto pressure = WaterEOS(2, 70);
    auto pressure_force = PressureForce(part_holder, part_prop, pressure);
    auto visc_force = MorrisLowViscosityForce(part_holder, part_prop, 0.05);
    auto ext_force = ExternalGravityForce(part_holder, part_prop, 5);
    auto force = Force(part_holder, part_prop, pressure_force, visc_force, ext_force);

    //Boundary Conditions
    auto physical_volume = Box(0, 10, 0, 8);
    auto boundary = ReflectiveRectangularBoundary(physical_volume, 0.95);

    //Density calculator
    auto density_calculator = ClassicDensityCalculator(part_holder, part_prop);

    //File writer
    auto project_folder = fs::current_path().parent_path();
    auto drop_folder = project_folder / "drop";
    if (not(fs::is_directory(drop_folder))) fs::create_directory(drop_folder);
    auto writer_kernel = SextaKernel();
    auto writer_part_prop = ParticleProperty(0.25, 1.0, writer_kernel);
    auto writer_density_calculator = ClassicDensityCalculator(part_holder, writer_part_prop);
    auto writer = ParticlePositionDensityWriter(part_holder, writer_density_calculator, drop_folder);
    writer.set_grid_params(physical_volume, 200, 200);
    writer.set_time_params(0, 30, 300);

    // Creating the World (requires 7 days)
    auto world = World(boundary, part_holder, part_prop, density_calculator, force, writer);
    auto t_start = std::chrono::high_resolution_clock::now();
    world.update(0, 30);
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout  << std::chrono::duration<double, std::milli>(t_end-t_start).count() << " ms" << std::endl;

    return 0;
}
