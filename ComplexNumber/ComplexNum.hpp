#ifndef COMPLEXNUM_HEADER
#define COMPLEXNUM_HEADER
#include <iostream>
//#define precision 0.00001

struct ComplexNum{
    double real;
    double im;

    ComplexNum(double real, double im);
    ComplexNum(const ComplexNum& another);
    ComplexNum();

    ~ComplexNum();

    ComplexNum FindConjugate() const;
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
    ComplexNum& operator+=(const ComplexNum& other);
    ComplexNum& operator+=(double x);
    ComplexNum& operator-=(const ComplexNum& other);
    ComplexNum& operator-=(double x);
    ComplexNum& operator*=(const ComplexNum& other);
    ComplexNum& operator*=(double x);
};
// оператор вывода
std::ostream& operator<< (std::ostream& os, const ComplexNum& z);

#endif