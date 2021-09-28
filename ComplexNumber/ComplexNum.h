#ifndef ComplexNum_header
#define ComplexNum_header
#include "iostream"
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

};
// оператор вывода
std::ostream& operator<< (std::ostream& os, const ComplexNum& z);

#endif