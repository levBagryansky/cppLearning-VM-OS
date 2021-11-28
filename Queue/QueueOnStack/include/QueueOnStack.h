#ifndef QUEUE_ON_STACK_H
#define QUEUE_ON_STACK_H

#include "QueueOnStack-impl.h"

template <>
class Queue<bool>{
public:
	Queue() = default;
	explicit Queue(size_t size);
	Queue(const Queue &other);
	Queue(Queue &&other) noexcept;
	~Queue();

	size_t GetSize() const;
	bool IsEmpty() const;
	void push(bool value);
	void pop();
	const bool & front();
	bool back();
	void swap(Queue &other);

private:
	Stack<bool> stack_to_push;
	Stack<bool> stack_to_pop;
};


#endif //QUEUE_ON_STACK_H