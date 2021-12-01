#ifndef QUEUE_ON_LIST_IMPL_H
#define QUEUE_ON_LIST_IMPL_H

#include "QueueOnList.h"

namespace OnList {
	template<class T>
	Queue<T>::Queue(): head_(nullptr), tail_(nullptr), size_(0) {}

	template<class T>
	Queue<T>::Queue(const Queue &other): size_(other.size_) {
		if (other.size_ == 0) {
			head_ = nullptr;
			tail_ = nullptr;
		} else {
			head_ = new Node<T>;
			head_->value = other.head_->value;
			Node<T> *curr_node = head_;
			Node<T> *buff_node = other.head_->next;
			while (buff_node != nullptr) {
				curr_node->next = new Node<T>;
				curr_node = curr_node->next;
				curr_node->value = buff_node->value;
				buff_node = buff_node->next;
			}
			tail_ = curr_node;
			tail_->next = nullptr;

		}

	}

	template<class T>
	Queue<T>::Queue(Queue<T> &&other) noexcept : head_(other.head_), tail_(other.tail_), size_(other.size_) {}

	template<class T>
	Queue<T>::~Queue() {
		if (size_) {
			Node<T> *buf_next = head_->next;
			Node<T> *buf_curr = head_;
			while (buf_next != nullptr) {
				delete buf_curr;
				buf_curr = buf_next;
				buf_next = buf_next->next;
			}
			delete buf_curr;
		}
	}

	template<class T>
	size_t Queue<T>::GetSize() const {
		return size_;
	}

	template<class T>
	bool Queue<T>::IsEmpty() const {
		return size_ == 0;
	}

	template<class T>
	void Queue<T>::push(T value) {
		if (size_) {
			tail_->next = new Node<T>;
			tail_ = tail_->next;
			tail_->next = nullptr;
			tail_->value = value;
			size_++;
		} else {
			tail_ = head_ = new Node<T>;
			tail_->next = nullptr;
			tail_->value = value;
			size_++;
		}
	}

	template<class T>
	void Queue<T>::pop() {
		if (size_ > 0) {
			Node<T> *buf = head_;
			head_ = head_->next;
			delete buf;
			size_--;
		} else {
			exit(1);
		}
	}

	template<class T>
	const T &Queue<T>::front() {
		if (size_ > 0) {
			return head_->value;
		} else {
			exit(1);
		}
	}

	template<class T>
	const T &Queue<T>::back() {
		if (size_ > 0) {
			return tail_->value;
		} else {
			exit(1);
		}
	}

	template<class T>
	void Queue<T>::swap(Queue<T> &other) {
		std::swap(size_, other.size_);
		std::swap(head_, other.head_);
		std::swap(tail_, other.tail_);
	}

	template<class T>
	Queue<T>& Queue<T>::operator=(const Queue<T> &other) {
		if (this == &other) {
			return *this;
		}

		//deleting
		if (size_) {
			Node<T> *buf_next = head_->next;
			Node<T> *buf_curr = head_;
			while (buf_next != nullptr) {
				delete buf_curr;
				buf_curr = buf_next;
				buf_next = buf_next->next;
			}
			delete buf_curr;
		}

		size_ = other.size_;
		if (other.size_ == 0) {
			head_ = nullptr;
			tail_ = nullptr;
		} else {
			head_ = new Node<T>;
			head_->value = other.head_->value;
			Node<T> *curr_node = head_;
			Node<T> *buff_node = other.head_->next;
			while (buff_node != nullptr) {
				curr_node->next = new Node<T>;
				curr_node = curr_node->next;
				curr_node->value = buff_node->value;
				buff_node = buff_node->next;
			}
			tail_ = curr_node;
			tail_->next = nullptr;
		}
		return *this;
	}

	template<class T>
	Queue<T>& Queue<T>::operator=(Queue<T> &&other) noexcept {
		if (this == &other){
			return *this;
		}

		head_ = other.head_;
		tail_ = other.tail_;
		size_ = other.size_;
	}

	template<class T>
	bool Queue<T>::operator==(const Queue<T> &other) const {
		if (size_ != other.size_){
			return false;
		}
		if (size_ == 0){
			return true;
		}

		Node<T>* buf = head_;
		Node<T>* buf_other = other.head_;

		while (buf != nullptr){
			if (buf->value != buf_other->value){
				return false;
			}

			buf = buf->next;
			buf_other = buf_other->next;
		}

		return true;
	}

	template<class T>
	bool Queue<T>::operator!=(const Queue<T> &other) const {
		return !(operator==(other));
	}
}
#endif  // QUEUE_ON_LIST_IMPL_H