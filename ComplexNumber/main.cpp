#include <iostream>
#include "ComplexNum.h"

int main() {
    ComplexNum z1 = ComplexNum(5, 7);
    ComplexNum z2;
    std::cout << "Enter complex number (a + bi):";
    z2.operator>>(std::cin);
    z1.AbsSquare();
    std::cout << "Your complex number equal ";
    z2.operator<<(std::cout) << std::endl;
    return 0;
}
