#include "ComplexNum.hpp"

ComplexNum::ComplexNum(double new_real, double new_im): real(new_real), im(new_im) {}

ComplexNum::ComplexNum(const ComplexNum& another): real(another.real), im(another.im){}

ComplexNum::ComplexNum(): real(0), im(0){}

ComplexNum::~ComplexNum() {
    real = 0;
    im = 0;
}
//Найти сопряженное
ComplexNum ComplexNum::conjugate() const{
    return ComplexNum(real, -im);
}
double ComplexNum::AbsSquare() const{
    return real * real - im * im;
}

ComplexNum& ComplexNum::operator=(const ComplexNum& other){
    im = other.im;
    real = other.real;

    return *this;
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

ComplexNum ComplexNum::operator-() const{
    return ComplexNum(-real, -im);
}

ComplexNum ComplexNum::operator*(const ComplexNum &other) const{
    return ComplexNum(real * other.real - im * other.im,
                      im * other.real + real * other.im);
}

ComplexNum ComplexNum::operator*(double k) const{
    return ComplexNum(real * k, im * k);
}

ComplexNum ComplexNum::operator/(const ComplexNum &other) const{
    ComplexNum res(*this);
    res.real = real * other.real + im * other.im;
    res.im = im * other.real - real * other.im;

    return res;
}

ComplexNum ComplexNum::operator/(double k) const{
    return ComplexNum(real / k, im / k);
}

bool ComplexNum::operator==(const ComplexNum &other) const{
    if (isEqual(im, other.im) && isEqual(real, other.real))
        return true;
    return false;
}

bool ComplexNum::operator!=(const ComplexNum &other) const{
    if (isEqual(im, other.im) && isEqual(real, other.real))
        return false;
    return true;
}

bool ComplexNum::operator==(double x) const {
    return (isEqual(real, x) && isEqual(im, 0));
}

bool ComplexNum::operator!=(double x) const{
    return !(isEqual(real, x) && isEqual(im, 0));
}

ComplexNum& ComplexNum::operator+=(const ComplexNum& other){
    im += other.im;
    real += other.real;

    return *this;
}

ComplexNum& ComplexNum::operator+=(double x){
    real += x;
    return *this;
}

ComplexNum& ComplexNum::operator-=(const ComplexNum& other){
    real -= other.real;
    im -= other.im;
    return *this;
}

ComplexNum& ComplexNum::operator-=(double x){
    real -= x;
    return *this;
}

ComplexNum& ComplexNum::operator*=(const ComplexNum& other){
    double bufReal = real;
    real = bufReal * other.real - im * other.im;
    im = im * other.real + bufReal * other.im;
    return *this;
}

ComplexNum& ComplexNum::operator*=(double x){
    real *= x;
    im *= x;
    return *this;
}

ComplexNum& ComplexNum::operator/=(const ComplexNum& other){
    double bufReal = real;
    real = real * other.real / other.AbsSquare() + im * other.im / other.AbsSquare();
    im = im * other.real / other.AbsSquare() - bufReal * other.im / other.AbsSquare();

    return *this;
}
ComplexNum& ComplexNum::operator/=(double x){
    real /= x;
    im  /= x;

    return *this;
}

std::ostream& operator<< (std::ostream& os, const ComplexNum& z){
    if (z.im < 0)
        os << z.real << " - " << -z.im << 'i';
    else if (z.im > 0)
        os << z.real << " + " << z.im << 'i';
    else
        os << z.real;
    return os;
}

ComplexNum operator+(double x, const ComplexNum& z){
    return ComplexNum(z.real + x, z.im);
}

ComplexNum operator-(double x, const ComplexNum& z){
    return ComplexNum(z.real - x, z.im);
}

ComplexNum operator*(double k, const ComplexNum& z){
    return {z.real * k, z.im * k};
}

ComplexNum operator/(double k, const ComplexNum& z){
    return {k * z.real / z.AbsSquare(), -k * z.im / z.AbsSquare()};
}

bool operator==(double x, const ComplexNum& z){
    return (isEqual(x, z.real) && isEqual(z.im, 0));
}

bool operator!=(double x, const ComplexNum& z){
    return !(isEqual(x, z.real) && isEqual(z.im, 0));
}

bool isEqual(double a, double b){
    return (abs(a - b) < 1e-8);
}
