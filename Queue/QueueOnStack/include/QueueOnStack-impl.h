#ifndef QUEUE_ON_STACK_IMPL_H
#define QUEUE_ON_STACK_IMPL_H

#include "../Stack/include/Stack.h"

template <class T>
class Queue{
public:
	Queue() = default;
	explicit Queue(size_t size);
	Queue(const Queue &other);
	Queue(Queue &&other) noexcept;
	~Queue() = default;

	size_t GetSize() const;
	bool IsEmpty() const;
	void push(T value);
	void pop();
	const T& front();
	const T& back();
	void swap(Queue &other);

private:
	Stack<T> stack_push_;
	Stack<T> stack_pop_;
};

template<class T>
Queue<T>::Queue(size_t size): stack_push_(size), stack_pop_(size){}

template<class T>
Queue<T>::Queue(const Queue &other): stack_push_(other.stack_push_), stack_pop_(other.stack_pop_){}

template<class T>
Queue<T>::Queue(Queue<T> &&other) noexcept: stack_push_(std::move(other.stack_push_)), stack_pop_(std::move(other.stack_pop_)){}

template<class T>
size_t Queue<T>::GetSize() const {
	return stack_push_.getSize() + stack_pop_.getSize();
}

template<class T>
bool Queue<T>::IsEmpty() const {
	return stack_pop_.isEmpty() && stack_push_.isEmpty();
}

template<class T>
void Queue<T>::push(T value) {
	stack_push_.push(value);
}

template<class T>
void Queue<T>::pop() {
	if (stack_pop_.isEmpty()){
		while (!stack_push_.isEmpty()){
			stack_pop_.push(stack_push_.top());
			stack_push_.pop();
		}
	}

	stack_pop_.pop();
}

template<class T>
const T& Queue<T>::front() {
	if (stack_pop_.isEmpty()){
		while (!stack_push_.isEmpty()){
			stack_pop_.push(stack_push_.top());
			stack_push_.pop();
		}
	}

	return stack_pop_.top();
}

template<class T>
const T& Queue<T>::back() {
	if (stack_push_.isEmpty()){
		while (!stack_pop_.isEmpty()){
			stack_push_.push(stack_pop_.top());
			stack_pop_.pop();
		}
	}

	return stack_push_.top();
}

template <class T>
void Queue<T>::swap(Queue<T> &other) {
	stack_push_.swap(other.stack_push_);
	stack_pop_.pop(other.stack_pop_);
}

#endif //QUEUE_ON_STACK_IMPL_H