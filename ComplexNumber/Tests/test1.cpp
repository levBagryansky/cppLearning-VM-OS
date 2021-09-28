#ifndef ComplexNumHeaderIncluded
#include "../ComplexNum.h"
#define ComplexNumHeaderIncluded 1
#endif

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
    if (!z1.operator==(z2))
        return false;

    ComplexNum z3(-5, -10);
    ComplexNum z4(-5, 10);
    if (z3.operator==(z4))
        return false;

    ComplexNum z5(99, 4);
    ComplexNum z6(99, 4);
    if (!z5.operator==(z6))
        return false;

    return true;
}

int correctPlus(){
    ComplexNum z1(0, 0);
    ComplexNum z2(2, 3);
    if (!((z1.operator+(z2)).operator==({2, 3})))
        return 1;

    z1 = ComplexNum(2, 4);
    z2 = ComplexNum(2, 4);
    if (!((z1.operator+(z2)).operator==({4, 8}))){
        (z1.operator+(z2)).operator<<(std::cout);
        std::cout << std::endl;
        return 2;
    }

    z1 = ComplexNum(-2, -4);
    z2 = ComplexNum(2, 4);
    if (!((z1.operator+(z2)).operator==({0, 0})))
        return 3;

    z1 = ComplexNum(-18, 20);
    z2 = ComplexNum(-2, 9);
    if (!((z1.operator+(z2)).operator==({-20, 29})))
        return 4;

    z1 = ComplexNum(4, 1);
    if (!((z1.operator+(9)).operator==({13, 1})))
        return 5;

    return 0;
}

int correctMinus(){
    ComplexNum z1(0, 0);
    ComplexNum z2(-2, -3);
    if (!z1.operator-(z2).operator==({2, 3}))
        return 1;

    z1 = ComplexNum(2, 4);
    z2 = ComplexNum(2, 4);
    if (!(z1.operator-(z2)).operator==({0, 0}))
        return 2;

    z1 = ComplexNum(-2, -4);
    z2 = ComplexNum(2, 4);
    if (!z1.operator-(z2).operator==({-4, -8}))
        return 3;

    z1 = ComplexNum(-18, 20);
    z2 = ComplexNum(-2, 9);
    if (!z1.operator-(z2).operator==({-16, 11}))
        return 4;

    z1 = ComplexNum(4, 1);
    if (!(z1.operator-(5)).operator==({-1, 1})){
        std::cout << (z1.operator-(5)).real << " + " <<
        (z1.operator-(5)).im << 'i' << std::endl;
        return 5;
    }
    return 0;
}

int correctMultiply(){
    ComplexNum z1(0, 0);
    ComplexNum z2(-2, -3);
    if (!((z1.operator*(z2)).operator==({0, 0}))){
        std::cout << z1.operator*(z2).real << " and " <<
        z1.operator*(z2).im << 'i' << std::endl;
        return 1;
    }

    z1 = ComplexNum(2, 4);
    z2 = ComplexNum(2, 4);
    if (!(z1.operator*(z2)).operator==({-12, 16}))
        return 2;

    z1 = ComplexNum(-2, -4);
    z2 = ComplexNum(2, 4);
    if (!z1.operator*(z2).operator==({12, -16}))
        return 3;

    z1 = ComplexNum(4, 1);
    if (!(z1.operator*(5)).operator==({20, 5})){
        std::cout << (z1.operator-(5)).real << " + " <<
                  (z1.operator-(5)).im << 'i' << std::endl;
        return 4;
    }
    return 0;
}

int test1(){
    int errorCode = 0;
    if ((errorCode = correctPlus()) != 0) {
        std::cout << "Plus is not correct, test: " << errorCode << std::endl;
    }

    if (correctEqual())
        ;//std::cout << "Equal is correct" << std::endl;
    else
        std::cout << "Equal is not correct" << std::endl;

    if((errorCode = correctMinus()) == 0)
        ;//std::cout << "Minus is equal" << std::endl;
    else{
        std::cout << "Minus is not correct, test: " <<
        errorCode << std::endl;
    }

    if ((errorCode = correctConstructors()) != 0){
        std::cout << "Constructor is not correct, test: " <<
        errorCode << std::endl;
    }

    if ((errorCode = correctMultiply()) != 0){
        std::cout << "Multiply is not correct, test: " <<
                  errorCode << std::endl;
    }

    std::cout << "Nice\n";
    return 0;
}
