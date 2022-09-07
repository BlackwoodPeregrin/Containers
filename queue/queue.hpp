#pragma once
#include <iostream>

template <typename T>
class Queue {
 public:
  Queue();
  explicit Queue(std::initializer_list<T> const &items);
  Queue(const Queue &q);
  Queue(Queue &&q);
  ~Queue();
  void operator=(Queue &&q);
  Queue &operator=(const Queue &q);

  const T &Front();
  const T &Back();

  bool IsEmpty();
  size_t Size();

  void Push(const T &value);
  T Pop();
  void swap(Queue &other);
  void clear();

 private:
  class Node {
   public:
    explicit Node(const T &data = T(), Node *next = nullptr)
        : m_next(next), m_data(data) {}
    Node *m_next;
    T m_data;
  };
  Node *m_front;
  Node *m_back;
  size_t m_size;
};

#include "queue.inl"
