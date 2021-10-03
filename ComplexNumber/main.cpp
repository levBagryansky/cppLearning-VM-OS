#include "ComplexNum.hpp"

int correctConstructors();
bool correctEqual();
int correctPlus();
int correctMinus();
int correctMultiply();
int correctconjugate();
int correctPlusAssign();
int correctMinusAssign();
int correctMultiplyAssign();
int test1();

int main() {
    test1();
    return 0;
}

int correctConstructors(){
    ComplexNum z1 = ComplexNum();
    if (!(z1.real == 0 && z1.im == 0))
        return 1;

    ComplexNum z2(1, 1);
    if(!(z2.im == 1 && z2.real == 1)){
        return 2;
    }

    ComplexNum z3(z2);
    if(!(z3.im == 1 && z3.real == 1)){
        return 3;
    }

    return 0;
}

bool correctEqual(){
    ComplexNum z1(0, 0);
    ComplexNum z2(0, 0);
    if (!(z1== z2))
        return false;

    ComplexNum z3(-5, -10);
    ComplexNum z4(-5, 10);
    if (z3 == z4)
        return false;

    ComplexNum z5(99, 4);
    ComplexNum z6(99, 4);
    if (!(z5 == z6))
        return false;

    return true;
}

int correctPlus(){
    ComplexNum z1(0, 0);
    ComplexNum z2(2, 3);
    if (!((z1 + z2) == ComplexNum{2, 3}))
        return 1;

    z1 = ComplexNum(2, 4);
    z2 = ComplexNum(2, 4);
    if (!((z1 + z2)== ComplexNum{4, 8})){
        std::cout << z1 + z2;
        std::cout << std::endl;
        return 2;
    }

    z1 = ComplexNum(-2, -4);
    z2 = ComplexNum(2, 4);
    if (!((z1 + z2) == ComplexNum{0, 0}))
        return 3;

    z1 = ComplexNum(-18, 20);
    z2 = ComplexNum(-2, 9);
    if (!((z1+ z2)==(ComplexNum{-20, 29})))
        return 4;

    z1 = ComplexNum(4, 1);
    if (!((z1+(9))==(ComplexNum{13, 1})))
        return 5;

    return 0;
}

int correctMinus(){
    ComplexNum z1(0, 0);
    ComplexNum z2(-2, -3);
    if (!(z1-(z2)==(ComplexNum{2, 3})))
        return 1;

    z1 = ComplexNum(2, 4);
    z2 = ComplexNum(2, 4);
    if (!((z1-(z2))==(ComplexNum{0, 0})))
        return 2;

    z1 = ComplexNum(-2, -4);
    z2 = ComplexNum(2, 4);
    if (!(z1-(z2)==(ComplexNum{-4, -8})))
        return 3;

    z1 = ComplexNum(-18, 20);
    z2 = ComplexNum(-2, 9);
    if (!(z1-(z2)==(ComplexNum{-16, 11})))
        return 4;

    z1 = ComplexNum(4, 1);
    if (!((z1-(5))== ComplexNum{-1, 1})){
        std::cout << (z1-(5)).real << " + " <<
                  (z1-(5)).im << 'i' << std::endl;
        return 5;
    }

    ComplexNum z3(-z1);
    if (!(z3 == ComplexNum{-4, -1})){
        std::cout << "z1 = " << z1 << ", z3 = " << z3 << std::endl;
        return 6;
    }

    return 0;
}

int correctMultiply(){
    ComplexNum z1(0, 0);
    ComplexNum z2(-2, -3);
    if (!((z1*(z2))==(ComplexNum{0, 0}))){
        std::cout << z1*(z2).real << " and " <<
                  z1*(z2).im << 'i' << std::endl;
        return 1;
    }

    z1 = ComplexNum(2, 4);
    z2 = ComplexNum(2, 4);
    if (!((z1 * z2) == ComplexNum{-12, 16}))
        return 2;

    z1 = ComplexNum(-2, -4);
    z2 = ComplexNum(2, 4);
    if (!(z1*z2==(ComplexNum{12, -16})))
        return 3;

    z1 = ComplexNum(4, 1);
    if (!((z1 * 5) == ComplexNum{20, 5})){
        std::cout << (z1 - 5).real << " + " <<
                  (z1 - 5).im << 'i' << std::endl;
        return 4;
    }
    return 0;
}

int correctconjugate(){
    ComplexNum z(1, 1);
    ComplexNum z_conjugate = z.conjugate();
    if (!(z_conjugate==(ComplexNum{1, -1})))
        return 1;

    z = ComplexNum(4, -3);
    z_conjugate = z.conjugate();
    if (!(z_conjugate == ComplexNum{4, 3}))
        return 2;

    return 0;
}

int correctPlusAssign(){
    ComplexNum z1(1, 1);
    z1+=(ComplexNum{2, 6});
    if (!(z1==(ComplexNum{3, 7})))
        return 1;

    z1+=(9);
    if (!(z1==ComplexNum({12, 7})))
        return 2;

    return 0;
}

int correctMinusAssign(){
    ComplexNum z1(1, 1);
    z1-= ComplexNum{2, 6};
    if (!(z1==(ComplexNum{-1, -5})))
        return 1;

    z1-=(4);
    if (!(z1 == ComplexNum{-5, -5}))
        return 2;

    return 0;
}

int correctMultiplyAssign(){
    ComplexNum z1(1, 1);
    z1 *= {2, 6};
    //std::cout << z1 << std::endl;
    if (!(z1==(ComplexNum{-4, 8})))
        return 1;

    z1*=(4);
    //std::cout << z1 << std::endl;
    if (!(z1==(ComplexNum{-16, 32})))
        return 2;

    return 0;
}

int test1(){
    int errorCode = 0;
    if ((errorCode = correctPlus())) {
        std::cout << "Plus is not correct, test: " << errorCode << std::endl;
    }

    if (!correctEqual())
        std::cout << "Equal is not correct" << std::endl;

    if((errorCode = correctMinus()))
    {
        std::cout << "Minus is not correct, test: " <<
                  errorCode << std::endl;
    }

    if ((errorCode = correctConstructors())){
        std::cout << "Constructor is not correct, test: " <<
                  errorCode << std::endl;
    }

    if ((errorCode = correctMultiply())){
        std::cout << "Multiply is not correct, test: " <<
                  errorCode << std::endl;
    }

    if ((errorCode = correctconjugate())){
        std::cout << "conjugate is not correct, test: " <<
                  errorCode << std::endl;
    }

    if ((errorCode = correctPlusAssign())){
        std::cout << "+= is not correct, test: " <<
                  errorCode << std::endl;
    }

    if ((errorCode = correctMinusAssign())){
        std::cout << "-= is not correct, test: " <<
                  errorCode << std::endl;
    }

    if ((errorCode = correctMultiplyAssign())){
        std::cout << "*= is not correct, test: " <<
                  errorCode << std::endl;
    }

    std::cout << "Nice\n";
    return 0;
}
