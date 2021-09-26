#include "ComplexNum.h"
#include "iostream"

ComplexNum operator+(const ComplexNum &z1, const ComplexNum &z2){
    return ComplexNum(z1.real_ + z2.real_, z1.im_ + z2.im_);
}

ComplexNum operator+(const ComplexNum &z1, double x){
    return ComplexNum(z1.real_ + x, z1.im_);
}

ComplexNum operator-(const ComplexNum &z1, const ComplexNum &z2){
    return ComplexNum(z1.real_ - z2.real_, z1.im_ - z2.im_);
}

ComplexNum operator-(const ComplexNum &z1, double x){
    return ComplexNum(z1.real_ - x, z1.im_);
}

ComplexNum operator*(const ComplexNum &z1, const ComplexNum &z2){
    return ComplexNum(z1.real_ * z2.real_ - z1.im_ * z2.im_,
                      z1.im_ + z2.im_);
}

ComplexNum operator*(const ComplexNum &z1, double k){
    return ComplexNum(z1.real_ * k,
                      z1.im_ * k);
}

ComplexNum operator/(const ComplexNum &z1, const ComplexNum &z2) {
    if (z2.real_ == 0 && z2.im_ == 0)
        throw std::invalid_argument("Cannot divide by 0");

    else {
        return z1 * z2 * (1 / z2.AbsSquare());
    }
}

ComplexNum operator/(const ComplexNum &z1, double k){
    if(k == 0)
        throw std::invalid_argument("Cannot divide by 0");
    return ComplexNum(z1.real_ / k,
                      z1.im_ / k);
}

bool operator==(const ComplexNum &z1, const ComplexNum &z2){
    if (z1.im_ == z2.im_ && z1.real_ == z2.real_)
        return true;
    return false;
}

std::ostream& operator<< (std::ostream& os, ComplexNum& z){
    if (z.im_ < 0)
        os << z.real_ << " - " << -z.im_ << 'i';
    else if (z.im_ > 0)
        os << z.real_ << " + " << z.im_ << 'i';
    else
        os << z.real_;
    return os;
}

std::istream& operator>> (std::istream& is, ComplexNum& z) {
    char c1;
    is >> z.real_ >> c1 >> z.im_;
    if ((c1 == '+' || c1 == '-')) {
        if (c1 == '-')
            z.im_ *= -1;
    }

    return is;
}