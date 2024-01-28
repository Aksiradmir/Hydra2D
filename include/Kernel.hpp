#pragma once

class Kernel
{
public:
    Kernel() {}
    virtual ~Kernel() {}
    virtual double kernel_function(double x) const = 0;
    virtual double kernel_function_derivative(double x) const = 0;
};


class CubicKernel : public Kernel
{
public:
    CubicKernel() {}
    virtual ~CubicKernel() {}
    virtual double kernel_function(double x) const;
    virtual double kernel_function_derivative(double x) const;
};


class CubicKernelSpiky : public Kernel
{
public:
    CubicKernelSpiky() {}
    virtual ~CubicKernelSpiky() {}
    virtual double kernel_function(double x) const;
    virtual double kernel_function_derivative(double x) const;
};


class CubicKernelViscosity : public Kernel
{
public:
    CubicKernelViscosity() {}
    virtual ~CubicKernelViscosity() {}
    virtual double kernel_function(double x) const;
    virtual double kernel_function_derivative(double x) const;
};


class SextaKernel : public Kernel
{
public:
    SextaKernel() {}
    virtual ~SextaKernel() {}
    virtual double kernel_function(double x) const;
    virtual double kernel_function_derivative(double x) const;
};