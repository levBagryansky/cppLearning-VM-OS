#ifndef QUEUE_ON_STACK_IMPL_H
#define QUEUE_ON_STACK_IMPL_H

#include "QueueOnStack.h"

namespace OnStack {

	template <class T>
	Queue<T>::Queue(size_t size) : stack_push_(size), stack_pop_(size) {}

	template <class T>
	Queue<T>::Queue(const Queue &other)
    	: stack_push_(other.stack_push_), stack_pop_(other.stack_pop_) {}

	template <class T>
	Queue<T>::Queue(Queue<T> &&other) noexcept
    	: stack_push_(std::move(other.stack_push_)),
      	stack_pop_(std::move(other.stack_pop_)) {}

	template <class T>
	size_t Queue<T>::GetSize() const {
	    return stack_push_.getSize() + stack_pop_.getSize();
	}

	template <class T>
	bool Queue<T>::IsEmpty() const {
    	return stack_pop_.isEmpty() && stack_push_.isEmpty();
	}

	template <class T>
	void Queue<T>::push(T value) {
    	stack_push_.push(value);
	}

	template <class T>
	void Queue<T>::pop() {
    	if (stack_pop_.isEmpty()) {
        	while (!stack_push_.isEmpty()) {
            	stack_pop_.push(stack_push_.top());
            	stack_push_.pop();
        	}
    	}

    	stack_pop_.pop();
	}

	template <class T>
	const T &Queue<T>::front() {
    	if (stack_pop_.isEmpty()) {
        	while (!stack_push_.isEmpty()) {
            	stack_pop_.push(stack_push_.top());
            	stack_push_.pop();
        	}
    	}
		const T& ret = stack_pop_.top();
    	return ret;
	}

	template <class T>
	const T& Queue<T>::back() {
    	if (stack_push_.isEmpty()) {
        	while (!stack_pop_.isEmpty()) {
				T buf = stack_pop_.top();
            	stack_push_.push(buf);
            	stack_pop_.pop();
        	}
    	}
		const T& ret = stack_push_.top();
	    return ret;
	}

	template <class T>
	void Queue<T>::swap(Queue<T> &other) {
    	stack_push_.swap(other.stack_push_);
    	stack_pop_.swap(other.stack_pop_);
	}

	template<class T>
	Queue<T>& Queue<T>::operator=(const Queue<T> &other) {
		stack_push_ = other.stack_push_;
		stack_pop_ = other.stack_pop_;
		return *this;
	}

	template<class T>
	Queue<T>& Queue<T>::operator=(Queue<T> &&other) noexcept {
		stack_push_ = std::move(other.stack_push_);
		stack_pop_ = std::move(other.stack_pop_);
	}

	template<class T>
	bool Queue<T>::operator==(Queue<T> &other) {
		if (GetSize() != other.GetSize()){
			return false;
		}

		size_t size = GetSize();
		Stack<T> stk_of_this(size);
		Stack<T> stk_of_other(size);

		for (size_t i = 0; i < size; ++i) {
			stk_of_this.push(front());
			stk_of_other.push(other.front());
			pop();
			other.pop();
		}

		bool ret = (stk_of_this == stk_of_other);

		for (size_t i = 0; i < size; ++i) {
			stack_push_.push(stk_of_this.top());
			other.stack_push_.push(stk_of_other.top());
			stk_of_this.pop();
			stk_of_other.pop();
		}

		return ret;
	}

	template<class T>
	bool Queue<T>::operator!=(Queue<T> &other){
		return !(operator==(other));
	}

}  // namespace OnStack

#endif  // QUEUE_ON_STACK_IMPL_H