#include "ComplexNum.h"
#include "iostream"

ComplexNum::ComplexNum(double real, double im){
    real_ = real;
    im_ = im;
}

ComplexNum::ComplexNum(const ComplexNum& another):
    real_(another.real_), im_(another.im_){}

ComplexNum::ComplexNum():
    real_(0), im_(0){}

//Найти сопряженное
ComplexNum ComplexNum::FindConjugate() const{
    return ComplexNum(real_, -im_);
}
double ComplexNum::AbsSquare() const{
    return real_ * real_ - im_ * im_;
}

ComplexNum ComplexNum::operator+(const ComplexNum &other) const{
    return ComplexNum( + other.real_, im_ + other.im_);
}

ComplexNum ComplexNum::operator+(double x) const{
    return ComplexNum(real_ + x, im_);
}

ComplexNum ComplexNum::operator-(const ComplexNum &other) const{
    return ComplexNum(real_ - other.real_, im_ - other.im_);
}

ComplexNum ComplexNum::operator-(double x) const{
    return ComplexNum(real_ - x, im_);
}

ComplexNum ComplexNum::operator*(const ComplexNum &other) const{
    return ComplexNum(real_ * other.real_ - im_ * other.im_,
                      im_ + other.im_);
}

ComplexNum ComplexNum::operator*(double k) const{
    return ComplexNum(real_ * k,
                      im_ * k);
}

ComplexNum ComplexNum::operator/(const ComplexNum &other) const{
    if (other.real_ == 0 && other.im_ == 0)
        throw std::invalid_argument("Cannot divide by 0");

    else {
        return this->operator*(other) * (1 / other.AbsSquare());
    }
}

ComplexNum ComplexNum::operator/(double k) const{
    if(k == 0)
        throw std::invalid_argument("Cannot divide by 0");
    return ComplexNum(real_ / k,
                      im_ / k);
}

bool ComplexNum::operator==(const ComplexNum &other) const{
    if (this->im_ == other.im_ && real_ == other.real_)
        return true;
    return false;
}

std::ostream& ComplexNum::operator<< (std::ostream& os){
    if (im_ < 0)
        os << real_ << " - " << -im_ << 'i';
    else if (im_ > 0)
        os << real_ << " + " << im_ << 'i';
    else
        os << real_;
    return os;
}

std::istream& ComplexNum::operator>> (std::istream& is){
    char c1;
    is >> real_ >> c1 >> im_;
    if ((c1 == '+' || c1 == '-')) {
        if (c1 == '-')
            im_ *= -1;
    }

    return is;
}