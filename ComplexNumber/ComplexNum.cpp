#include "ComplexNum.h"
#include <iostream>

ComplexNum::ComplexNum(double new_real, double new_im): real(new_real), im(new_im) {}

ComplexNum::ComplexNum(const ComplexNum& another):
    real(another.real), im(another.im){}

ComplexNum::ComplexNum():
    real(0), im(0){}

//Найти сопряженное
ComplexNum ComplexNum::FindConjugate() const{
    return ComplexNum(real, -im);
}
double ComplexNum::AbsSquare() const{
    return real * real - im * im;
}

ComplexNum ComplexNum::operator+(const ComplexNum &other) const{
    return ComplexNum(real + other.real, im + other.im);
}

ComplexNum ComplexNum::operator+(double x) const{
    return ComplexNum(real + x, im);
}

ComplexNum ComplexNum::operator-(const ComplexNum &other) const{
    return ComplexNum(real - other.real, im - other.im);
}

ComplexNum ComplexNum::operator-(double x) const{
    return ComplexNum(real - x, im);
}

ComplexNum ComplexNum::operator*(const ComplexNum &other) const{
    return ComplexNum(real * other.real - im * other.im,
                      im * other.real + real * other.im);
}

ComplexNum ComplexNum::operator*(double k) const{
    return ComplexNum(real * k,
                      im * k);
}

ComplexNum ComplexNum::operator/(const ComplexNum &other) const{
    if (other.real == 0 && other.im == 0)
        ;
    else {
        return this->operator*(other) * (1 / other.AbsSquare());
    }
}

ComplexNum ComplexNum::operator/(double k) const{
    if(k == 0)
    return ComplexNum(real / k, im / k);
}

bool ComplexNum::operator==(const ComplexNum &other) const{
    if (this->im == other.im && real == other.real)
        return true;
    return false;
}

std::ostream& ComplexNum::operator<< (std::ostream& os){
    if (im < 0)
        os << real << " - " << -im << 'i';
    else if (im > 0)
        os << real << " + " << im << 'i';
    else
        os << real;
    return os;
}

std::istream& ComplexNum::operator>> (std::istream& is){
    char c1;
    is >> real >> c1 >> im;
    if ((c1 == '+' || c1 == '-')) {
        if (c1 == '-')
            im *= -1;
    }

    return is;
}