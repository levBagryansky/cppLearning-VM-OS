/*
 * Реализация класса рациональых чисел Rational с перегрузкой операторов +, -, ==, !=, <, >, <<, >>.
 */

#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include <map>
#include <cmath>

using namespace std;

void sortAB(int* pa, int* pb) {// Старый код для поиска нод

    if (*pa < *pb)
    {
        int buf = *pa;
        *pa = *pb;
        *pb = buf;
    }
}

int calculateGCF(int a, int b){ // НОД

    if (a == b)
        return a;
    if (a == 0)
        return b;
    if (b == 0)
        return a;

    sortAB(&a, &b); // сортирует так, чтобы b было >= a

    int c = a % b;
    while (c != 0)
    {
        a = b;
        b = c;
        c = a % b;
    }

    return abs(b);
}


class Rational {
public:
    //Rational(){;}
    Rational(int numerator = 0, int denominator = 1){
        if (denominator == 0){
            throw invalid_argument("Denominator must not be 0");
        }

        int gcf = calculateGCF(numerator, denominator);
        p = numerator / gcf;
        q = denominator / gcf;

        if(p > 0 && q < 0){
            p *= -1;
            q *= -1;
        }

        //cout << "Created new Rational: p = " << p << ", q = " << q << endl;
    }

    int Numerator() const{
        return p;
    }
    int Denominator() const{
        return q;
    }

private:
    int p = 0;
    int q = 1;
};

bool operator== (const Rational& r1, const Rational& r2){
    return (r1.Denominator() == r2.Denominator() &&
            r1.Numerator() == r2.Numerator());

}

bool operator!= (const Rational& r1, const Rational& r2){
    return !(r1.Denominator() == r2.Denominator() &&
             r1.Numerator() == r2.Numerator());

}

Rational operator+ (const Rational& r1, const Rational& r2){
    int newNumerator = r1.Numerator() * r2.Denominator() + r2.Numerator() * r1.Denominator();
    int newDenominator = r1.Denominator() * r2.Denominator();
    return Rational(newNumerator, newDenominator);
}

Rational operator- (const Rational& r1, const Rational& r2){
    int newNumerator = r1.Numerator() * r2.Denominator() - r2.Numerator() * r1.Denominator();
    int newDenominator = r1.Denominator() * r2.Denominator();
    return Rational(newNumerator, newDenominator);
}

Rational operator* (const Rational& r1, const Rational& r2){
    int newNumerator = r1.Numerator() * r2.Numerator();
    int newDenominator = r1.Denominator() * r2.Denominator();
    return Rational(newNumerator, newDenominator);
}

Rational operator/ (const Rational& r1, const Rational& r2){
    int newDenominator = r1.Denominator() * r2.Numerator();
    if (newDenominator == 0)
        throw domain_error("You cannot divide by 0");

    int newNumerator = r1.Numerator() * r2.Denominator();
    return Rational(newNumerator, newDenominator);
}

ostream& operator<< (ostream& stream, const Rational& r){
    stream << r.Numerator() << '/' << r.Denominator();
    return stream;
}

istream& operator>> (istream& stream, Rational& r){
    int p = 0;
    if (!(stream >> p))
        return stream;
    //cout << "p = " << p << endl;

    char separator = 0;
    if (!(stream >> separator) || separator != '/')
        return stream;

    int q = 0;
    if(!(stream >> q))
        return stream;
    //cout << "q = " << q << endl;

    r = Rational(p, q);
    return stream;
}

bool operator< (const Rational& r1, const Rational& r2){
    int gsf = calculateGCF(r1.Denominator(), r2.Denominator());
    return (r1.Numerator() * (r2.Denominator() / gsf) <
            r2.Numerator() * (r1.Denominator() / gsf));
}

bool operator> (const Rational& r1, const Rational& r2){
    int gsf = calculateGCF(r1.Denominator(), r2.Denominator());
    return (r1.Numerator() * (r2.Denominator() / gsf) >
            r2.Numerator() * (r1.Denominator() / gsf));
}

int main() {
    {
        const set<Rational> rs = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};
        if (rs.size() != 3) {
            cout << "Wrong amount of items in the set" << endl;
            return 1;
        }

        vector<Rational> v;
        for (auto x : rs) {
            v.push_back(x);
        }
        if (v != vector<Rational>{{1, 25}, {1, 2}, {3, 4}}) {
            cout << "Rationals comparison works incorrectly" << endl;
            return 2;
        }
    }

    {
        map<Rational, int> count;
        ++count[{1, 2}];
        ++count[{1, 2}];

        ++count[{2, 3}];

        if (count.size() != 2) {
            cout << "Wrong amount of items in the map" << endl;
            return 3;
        }
    }
    try {
        Rational r(1, 0);
        cout << "Doesn't throw in case of zero denominator" << endl;
        return 4;
    } catch (invalid_argument&) {
    }

    try {
        auto x = Rational(1, 2) / Rational(0, 1);
        cout << "Doesn't throw in case of division by zero" << endl;
        return 5;
    } catch (domain_error&) {
    }

    cout << "OK" << endl;
    return 0;
}