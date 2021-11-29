#ifndef QUEUE_ON_STACK_H
#define QUEUE_ON_STACK_H

//#include "QueueOnStack-impl.h"
#include "../Stack/include/Stack.h"

namespace OnStack {

	template <class T>
	class Queue {
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
		const T &front();
		const T &back();
		void swap(Queue &other);

		Queue& operator=(const Queue& other);
		Queue& operator=(Queue&& other) noexcept;
		bool operator==(Queue<T>& other);
		bool operator!=(Queue<T>& other);

	private:
		Stack<T> stack_push_;
		Stack<T> stack_pop_;
	};

}  // namespace OnStack

#endif  // QUEUE_ON_STACK_H