#ifndef QUEUE_ON_LIST_H
#define QUEUE_ON_LIST_H

namespace OnList{
	template<class T>
	struct Node{
		T value;
		Node *next;
	};

	template<class T>
	class Queue {
	public:
		Queue();
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

	private:
		Node<T> *head_;
		Node<T> *tail_;
		size_t size_;

	};
}

#endif // QUEUE_ON_LIST_H