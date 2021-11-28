#ifndef QUEUE_ON_STACK_H
#define QUEUE_ON_STACK_H

#include "QueueOnStack-impl.h"

namespace OnStack {

template <>
class Queue<bool> {
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
    const bool &front();
    bool back();
    void swap(Queue &other);

   private:
    Stack<bool> stack_to_push_;
    Stack<bool> stack_to_pop_;
};

}  // namespace OnStack

#endif  // QUEUE_ON_STACK_H