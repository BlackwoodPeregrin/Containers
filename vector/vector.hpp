#pragma once

#include <limits>

template <class T>
class Vector {
 public:
  using iterator = T *;
  using const_iterator = const iterator;

 private:
  T *m_buffer;
  size_t m_capacity;
  size_t m_size;

 public:
  Vector();
  explicit Vector(size_t n);
  Vector(const std::initializer_list<T> &items);
  Vector(const Vector &v);
  Vector(Vector &&v);
  ~Vector();
  void clear();

  Vector &operator=(const Vector &v);
  Vector &operator=(Vector &&v);

  bool empty();
  size_t size();
  size_t capacity();
  size_t max_size();

  void shrink_to_fit() { _Redistribution(m_size); }
  void reserve(size_t size) {
    if (size > max_size()) {
      throw std::out_of_range("Cannot allocate such memory amount");
    }
    _Redistribution(size);
  }

  const T &front();
  const T &back();

  T &operator[](size_t pos);
  T &at(size_t pos);

  iterator begin();
  iterator end();

  iterator insert(iterator pos, const T &value);
  void erase(const_iterator pos);

  void push_back(const T &value);
  void pop_back();
  void swap(Vector &other);

 private:
  void _Redistribution2x();
  void _Redistribution(size_t size);
  void _Redistribution(size_t newm_size, iterator &iter);
};

#include "vector.inl"
