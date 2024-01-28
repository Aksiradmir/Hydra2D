#pragma once

#include <cmath>
#include <iostream>

class PressureEOS
{
public:
    PressureEOS() {}
    virtual ~PressureEOS() {}
    virtual double evaluate(double density) const = 0;
};


class LinearPressureEOS : public PressureEOS
{
private:
    double conversion_coeff;
    double target_density; 
public:
    LinearPressureEOS(double conversion_coeff, double target_density);
    virtual ~LinearPressureEOS() {}
    virtual double evaluate(double density) const;
};


class WaterEOS : public PressureEOS
{
private:
    double target_pressure;
    double target_density; 
public:
    WaterEOS(double target_pressure, double target_density);
    virtual ~WaterEOS() {}
    virtual double evaluate(double density) const;
};




