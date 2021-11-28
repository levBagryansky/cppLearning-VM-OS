#include "QueueOnStack.h"
#include "QueueOnList-impl.h"
#include <iostream>

int main() {
	std::cout << "Hello, World!" << std::endl;
	OnStack::Queue<int> q = OnStack::Queue<int>(5);
	for (int i = 0; i < 100; ++i) {
		q.push(i);
	}

	for (int i = 0; i < 100; ++i) {
		std::cout << q.front() << " ";
		q.pop();
	}
	std::cout << std::endl;
	return 0;
}
