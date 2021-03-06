#ifndef COMPLEXNUM_HPP
#define COMPLEXNUM_HPP
#include <iostream>

struct ComplexNum{
    double real;
    double im;

    ComplexNum(double real, double im);
    ComplexNum(const ComplexNum& another);
    ComplexNum();

    ~ComplexNum();

    ComplexNum conjugate() const;
    double AbsSquare() const;

    ComplexNum& operator=(const ComplexNum& other);
    ComplexNum operator+(const ComplexNum &other) const;
    ComplexNum operator+(double x) const;
    ComplexNum operator-(const ComplexNum &other) const;
    ComplexNum operator-(double x) const;
    ComplexNum operator-()const;
    ComplexNum operator*(const ComplexNum &other) const;
    ComplexNum operator*(double k) const;
    ComplexNum operator/(const ComplexNum &other) const;
    ComplexNum operator/(double k) const;
    bool operator==(const ComplexNum &other) const;
    bool operator!=(const ComplexNum &other) const;
    bool operator==(double x) const;
    bool operator!=(double x) const;
    ComplexNum& operator+=(const ComplexNum& other);
    ComplexNum& operator+=(double x);
    ComplexNum& operator-=(const ComplexNum& other);
    ComplexNum& operator-=(double x);
    ComplexNum& operator*=(const ComplexNum& other);
    ComplexNum& operator*=(double x);
    ComplexNum& operator/=(const ComplexNum& other);
    ComplexNum& operator/=(double x);
};

std::ostream& operator<< (std::ostream& os, const ComplexNum& z);
ComplexNum operator+(double x, const ComplexNum& z);
ComplexNum operator-(double x, const ComplexNum& z);
ComplexNum operator*(double k, const ComplexNum& z);
ComplexNum operator/(double k, const ComplexNum& z);
bool operator==(double x, const ComplexNum& z);
bool operator!=(double x, const ComplexNum& z);

bool isEqual(double a, double b);

#endif