#include "QueueOnStack.h"
#include <iostream>

int main() {
	std::cout << "Hello, World!" << std::endl;
	Queue<int> q = Queue<int>(5);
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
