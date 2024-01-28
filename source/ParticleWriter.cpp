#include "ParticleWriter.hpp"


ParticleWriter::ParticleWriter(ParticleHolder &particle_holder) : particle_holder(&particle_holder)
{
}





ParticlePositionTXTWriter::ParticlePositionTXTWriter(ParticleHolder &particle_holder, std::string &filename) : ParticleWriter(particle_holder)
{
    file = std::ofstream(filename);
}

void ParticlePositionTXTWriter::write(double time)
{
    file << std::setw(15) << time;
    size_t number_of_particles = particle_holder->get_number_of_particles();
    for (size_t i = 0; i < number_of_particles; i++)
    {
        file << std::setw(15) << particle_holder->get_particle(i).position.x;
    }
    file << '\n' << std::setw(15) << time;
    for (size_t i = 0; i < number_of_particles; i++)
    {
        file << std::setw(15) << particle_holder->get_particle(i).position.y;
    }
    file << '\n';
}






ParticlePositionDensityWriter::ParticlePositionDensityWriter(ParticleHolder &particle_holder, DensityCalculator &density_calculator, fs::path drop_folder) : ParticleWriter(particle_holder), density_calculator(&density_calculator), drop_folder(drop_folder)
{
    fs::path position_filename = drop_folder / "position_evo.txt";
    if (not(fs::is_directory(drop_folder / "density"))) fs::create_directory(drop_folder / "density");
    pos_file = std::ofstream(position_filename);
    time_print_iter = 0;
}

void ParticlePositionDensityWriter::set_grid_params(Box &box, int nx, int ny)
{
    this->box = &box;
    this->nx = nx;
    this->ny = ny;
    if (nx < 2) {
        std::cerr << "Error: nx in ParticlePositionDensityWriter::set_grid_params() must be greater than 2." << std::endl;
        std::exit(1);
    }
    if (ny < 2) {
        std::cerr << "Error: ny in ParticlePositionDensityWriter::set_grid_params() must be greater than 2." << std::endl;
        std::exit(1);
    }
    dx = (box.get_xmax() - box.get_xmin()) / (nx - 1);
    dy = (box.get_ymax() - box.get_ymin()) / (ny - 1);
    densities.resize(nx * ny);
}

void ParticlePositionDensityWriter::set_time_params(double t_start, double t_stop, int64_t n_steps)
{
    if (t_stop < t_start) {
        std::cerr << "Error: Start time must be less than stop time in WParticlePositionDensityWriter::set_time_params()." << std::endl;
        std::exit(1);
    }
    if (n_steps <= 0) {
        std::cerr << "Error: Number of time steps in ParticlePositionDensityWriter::set_time_params() must be greater than zero." << std::endl;
        std::exit(1);
    }
    this->current_print_time = t_start;
    this->time_step = (t_stop - t_start) / (n_steps - 1);
}

void ParticlePositionDensityWriter::write(double time)
{
    if (time_step > 0.0)
    {
        if (time >= current_print_time) {
            this->write_positions(time);
            this->write_densities(time);
            current_print_time += time_step;
        }
    }
}

void ParticlePositionDensityWriter::write_positions(double time)
{
    pos_file << std::setw(15) << time;
    size_t number_of_particles = particle_holder->get_number_of_particles();
    for (size_t i = 0; i < number_of_particles; i++)
    {
        pos_file << std::setw(15) << particle_holder->get_particle(i).position.x;
    }
    pos_file << '\n' << std::setw(15) << time;
    for (size_t i = 0; i < number_of_particles; i++)
    {
        pos_file << std::setw(15) << particle_holder->get_particle(i).position.y;
    }
    pos_file << '\n';
}

void ParticlePositionDensityWriter::write_densities(double time)
{
    if (nx and ny)
    {
        fs::path filename = drop_folder / std::format("density/density_time_iter_{}.txt", time_print_iter);
        auto dens_file = std::ofstream(filename);
        dens_file << "# Time " << time << "\n";
        this->evaluate_densities();
        for (size_t i = 0; i < ny; i++)
        {
            for (size_t j = 0; j < nx; j++)
            {
                dens_file << std::setw(15) << densities[i * ny + j];
            }
            dens_file << '\n';
        }
        time_print_iter++;
    }
}

void ParticlePositionDensityWriter::evaluate_densities()
{
    double* data_ptr = densities.data();
    #pragma omp parallel for
    for (size_t i = 0; i < ny; i++)
        {
            for (size_t j = 0; j < nx; j++)
            {
                Vector2D grid_point(j * dx, i * dy);
                data_ptr[i * ny + j] = density_calculator->calc_density_in_point(grid_point);
            }
        }
}
