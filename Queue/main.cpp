#include "QueueOnStack-impl.h"
#include "QueueOnList-impl.h"
#include <iostream>
#include <vector>

using namespace OnStack;

int main() {

	Queue<bool> bools1;
	Queue<bool> bools2;
	for (int i = 0; i < 1; ++i) {
		bools1.push(false);
		bools2.push(true);
	}
	//bools1.swap(bools2);
	std::cout << "bools1 == bools2:  " << (bools1 == bools2) << std::endl;

	return 0;
}
