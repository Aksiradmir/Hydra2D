#pragma once

#include "ParticleHolder.hpp"
#include "Box.hpp"
#include "DensityCalculator.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <format>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

class ParticleWriter
{
protected:
    ParticleHolder* particle_holder;
public:
    explicit ParticleWriter(ParticleHolder& particle_holder);
    virtual ~ParticleWriter() {}
    virtual void write(double time) {}
};


class ParticlePositionTXTWriter : public ParticleWriter
{
private:
    std::ofstream file;
public:
    ParticlePositionTXTWriter(ParticleHolder& particle_holder, std::string& filename);
    virtual ~ParticlePositionTXTWriter() {}
    virtual void write(double time);
};



class ParticlePositionDensityWriter : public ParticleWriter
{
private:
    DensityCalculator* density_calculator;
    std::ofstream pos_file;
    fs::path drop_folder;
    Box* box;
    size_t nx;
    size_t ny;
    double dx;
    double dy;
    double current_print_time;
    double time_step;
    size_t time_print_iter;
    std::vector<double> densities;
    
public:
    ParticlePositionDensityWriter(ParticleHolder& particle_holder, DensityCalculator& density_calculator, fs::path drop_folder);
    void set_grid_params(Box& box, int nx, int ny);
    void set_time_params(double t_start, double t_stop, int64_t n_steps);
    virtual ~ParticlePositionDensityWriter() {}
    virtual void write(double time);
    void write_positions(double time);
    void write_densities(double time);
    void evaluate_densities();
};


