#include <iostream>
#include "ComplexNum.h"

int main() {
    ComplexNum z1 = ComplexNum(5, 7);
    ComplexNum z2;
    z2.operator<<(std::cout << "Enter complex number (a + bi):");
    z2.operator<<(std::cout) << "";
    z2.operator>>(std::cin);
    z1.AbsSquare();
    std::cout << "z2 equal ";
    z2.operator<<(std::cout) << std::endl;
    return 0;
}
