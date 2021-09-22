#include <iostream>
#include <valarray>

struct ComplexNum{
    double real_;
    double im_;

public:
    ComplexNum(double real, double im);
    ComplexNum(const ComplexNum& another);
    ComplexNum();
    ComplexNum FindConjugate() const;
    double AbsSquare() const;
};

ComplexNum::ComplexNum(double real, double im){
    real_ = real;
    im_ = im;
}

ComplexNum::ComplexNum(const ComplexNum& another):
    real_(another.real_), im_(another.im_){}

ComplexNum::ComplexNum():
    real_(1), im_(0) {}

ComplexNum ComplexNum::FindConjugate() const{
    return {real_, -im_};
}

double ComplexNum::AbsSquare() const{
    return real_ * real_ + im_*im_;
}

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

std::ostream& operator<< (std::ostream& os, ComplexNum& z){
    if (z.im_ < 0)
        os << z.real_ << " - " << -z.im_ << 'i';
    else if (z.im_ > 0)
        os << z.real_ << " + " << z.im_ << 'i';
    else
        os << z.real_;
}

std::istream& operator>> (std::istream& is, ComplexNum& z){
    char c1;
    is >> z.real_ >> c1 >> z.im_;
    if ((c1 == '+' || c1 == '-')) {
        if (c1 == '-')
            z.im_ *= -1;
    } else
        throw std::runtime_error("Wrong format");

}

int main() {
    ComplexNum z1 = ComplexNum(5, 7);
    ComplexNum z2;
    std::cin >> z2;
    z1.AbsSquare();
    std::cout << "z2 equal " << z2 << std::endl;
    return 0;
}
