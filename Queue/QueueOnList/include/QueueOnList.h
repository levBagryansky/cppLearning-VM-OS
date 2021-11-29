#ifndef QUEUE_ON_LIST_H
#define QUEUE_ON_LIST_H

namespace OnList{
	template<class T>
	struct Node{
		T value;
		Node<T> *next;
	};

	template<class T>
	class Queue {
	public:
		Queue();
		Queue(const Queue &other);
		Queue(Queue &&other) noexcept;
		~Queue();

		size_t GetSize() const;
		bool IsEmpty() const;
		void push(T value);
		void pop();
		const T &front();
		const T &back();
		void swap(Queue &other);

		Queue& operator=(const Queue& other);
		Queue& operator=(Queue&& other) noexcept;
		bool operator==(const Queue<T>& other) const;
		bool operator!=(const Queue<T>& other) const;


	private:
		Node<T> *head_;
		Node<T> *tail_;
		size_t size_;

	};
}

#endif // QUEUE_ON_LIST_H