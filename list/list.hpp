#pragma once
#include <iostream>

template <typename T>
class List {
 public:
  List();
  explicit List(size_t n);
  List(std::initializer_list<T> const &items);
  List(const List &other);
  List(List &&other);
  ~List();
  void clear();

  List &operator=(const List &other);
  List &operator=(List &&other);
  void swap(List &other);

  const T &front();
  const T &back();

  void push_back(const T &value);
  void push_front(const T &value);
  T pop_back();
  T pop_front();
  bool equal(const List &other);

  bool empty() const;
  size_t size() const;
  size_t max_size() const;

 private:
  class Node {
   public:
    Node(const T &data, Node *prev, Node *next)
        : m_data(data), m_prev(prev), m_next(next) {}

    T m_data;
    Node *m_prev;
    Node *m_next;
  };

  /*----------Iterator----------*/
 public:
  class Iterator {
   public:
    Iterator();
    Iterator(const Iterator &other);
    Iterator(Iterator &&other);
    Iterator(Node *node);
    ~Iterator() = default;

    Iterator &operator=(const Iterator &other);
    Iterator &operator=(Iterator &&other);

    Iterator &operator++();
    Iterator &operator--();
    T &operator*();
    bool operator==(const Iterator &other);
    bool operator!=(const Iterator &other);

   protected:
    Node *m_cur;
  };

  Iterator begin() { return Iterator(m_begin); }
  Iterator end() { return Iterator(m_end); }

  /*----------Const Iterator----------*/
  class ConstIterator : public Iterator {
   public:
    ConstIterator() : Iterator() {}
    ConstIterator(const ConstIterator &other) : Iterator(other){};
    ConstIterator(ConstIterator &&other) : Iterator(other){};
    ConstIterator(Node *node) : Iterator(node){};
    ~ConstIterator() = default;

    ConstIterator &operator=(const ConstIterator &other) {
      Iterator::operator=(other);
      return *this;
    }
    ConstIterator &operator=(ConstIterator &&other) {
      Iterator::operator=(std::move(other));
      return *this;
    }
    const T &operator*() {
      if (this->m_cur == nullptr) {
        throw std::out_of_range("operator*:");
      }
      return this->m_cur->m_data;
    }
    bool operator==(const ConstIterator &other) {
      return Iterator::operator==(other);
    }
    bool operator!=(const ConstIterator &other) {
      return Iterator::operator!=(other);
    }
  };

  ConstIterator cbegin() { return ConstIterator(m_begin); }
  ConstIterator cend() { return ConstIterator(m_end); }

  bool erase(Iterator pos);
  Iterator insert(Iterator pos, const T &value);
  void splice(ConstIterator pos, List &other);
  void reverse();
  void sort();
  void unique();

 private:
  enum TypePushPop { kFront, kBack };
  void Push_(const T &value, bool type_push);
  T Pop_(bool type_pop);
  T PopLastElement_();

 private:
  Node *m_head;
  Node *m_tail;

  Node *m_begin;
  Node *m_end;

  size_t m_size;
};

#include "list.inl"
