#ifndef QUEUE_ON_LIST_IMPL_H
#define QUEUE_ON_LIST_IMPL_H

#include "QueueOnList.h"

namespace OnList{
	template<class T>
	Queue<T>::Queue(): head_(NULL), tail_(NULL), size_(0) {}

	template<class T>
	Queue<T>::Queue(size_t size): head_(NULL), tail_(NULL), size_(0){}

	template<class T>
	Queue<T>::Queue(const Queue &other): size_(other.size_) {

	}
}

#endif  // QUEUE_ON_LIST_IMPL_H