#pragma once
#include <iostream>

template <typename T>
class Stack {
 public:
  Stack();
  Stack(std::initializer_list<T> const &items);
  Stack(const Stack &s);
  Stack(Stack &&s);
  ~Stack();
  Stack &operator=(const Stack &s);
  Stack &operator=(Stack &&s);

  size_t Size();
  bool IsEmpty();

  const T &Top();
  T Pop();
  void Push(const T &value);
  void Swap(Stack &other);
  void Clear();

 private:
  class Node {
   public:
    Node(const T &data = T(), Node *next = nullptr)
        : m_next(next), m_data(data) {}
    Node *m_next;
    T m_data;
  };

 private:
  Node *m_head;
  size_t m_size;
};

#include "stack.inl"
