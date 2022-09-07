#pragma once

#include <iostream>

#include "../balance_tree/AvlTree.hpp"

template <class Key>
class Set : public AvlBalanceTree<Key, std::nullptr_t> {
 public:
  Set() : AvlBalanceTree<Key, std::nullptr_t>() {}
  Set(const Set &other) : AvlBalanceTree<Key, std::nullptr_t>(other) {}
  Set(const std::initializer_list<Key> &items) {
    for (const Key &value : items) {
      Insert(value);
    }
  }
  Set(Set &&other) : AvlBalanceTree<Key, std::nullptr_t>(std::move(other)) {}
  ~Set() {}

  Set &operator=(const Set &other) {
    AvlBalanceTree<Key, std::nullptr_t>::operator=(other);
    return *this;
  }

  Set &operator=(Set &&other) {
    AvlBalanceTree<Key, std::nullptr_t>::operator=(std::move(other));
    return *this;
  }

 public:
  class Iterator : public TreeIterator<Key, std::nullptr_t> {
   public:
    Iterator() : TreeIterator<Key, std::nullptr_t>(){};
    Iterator(const Iterator &other)
        : TreeIterator<Key, std::nullptr_t>(other) {}
    Iterator(NodeTree<Key, std::nullptr_t> *node)
        : TreeIterator<Key, std::nullptr_t>(node) {}
    Iterator(Iterator &&other)
        : TreeIterator<Key, std::nullptr_t>(std::move(other)) {}
    ~Iterator() {}

    Iterator &operator=(const Iterator &other) {
      TreeIterator<Key, std::nullptr_t>::operator=(other);
      return *this;
    }

    Iterator &operator=(Iterator &&other) {
      TreeIterator<Key, std::nullptr_t>::operator=(std::move(other));
      return *this;
    }

    Iterator &operator=(
        const AvlBalanceTree<int, std::nullptr_t>::Iterator &other) {
      TreeIterator<Key, std::nullptr_t>::operator=(other);
      return *this;
    }

    bool operator!=(const Iterator &other) {
      return TreeIterator<Key, std::nullptr_t>::operator!=(other);
    }
    bool operator==(const Iterator &other) {
      return TreeIterator<Key, std::nullptr_t>::operator==(other);
    }

    const Key &operator*() {
      if (this->m_cur == nullptr) {
        throw std::out_of_range("iterator nullptr");
      }
      return this->m_cur->m_key_value.first;
    }
  };

 public:
  Iterator begin() { return Iterator(this->m_begin); }
  Iterator end() { return Iterator(this->m_end); }

 public:
  class ConstIterator : public Iterator {
   public:
    ConstIterator() : Iterator() {}
    ConstIterator(const ConstIterator &other) : Iterator(other) {}
    ConstIterator(NodeTree<Key, std::nullptr_t> *node) : Iterator(node) {}
    ConstIterator(ConstIterator &&other) : Iterator(std::move(other)) {}
    ~ConstIterator() {}

    ConstIterator &operator=(const ConstIterator &other) {
      Iterator::operator=(other);
      return *this;
    }
    ConstIterator &operator=(ConstIterator &&other) {
      Iterator::operator=(std::move(other));
      return *this;
    }

    bool operator!=(const ConstIterator &other) {
      return Iterator::operator!=(other);
    }
    bool operator==(const ConstIterator &other) {
      return Iterator::operator==(other);
    }
  };

 public:
  ConstIterator cbegin() { return ConstIterator(this->m_begin); }
  ConstIterator cend() { return ConstIterator(this->m_end); }

  std::pair<Iterator, bool> Insert(const Key &key) {
    Iterator iter;
    size_t size = this->m_size;
    std::pair<Key, std::nullptr_t> key_value{key, std::nullptr_t()};
    if (this->m_root == nullptr) {
      iter = this->AddFirstElement_(key_value);
    } else {
      iter = this->AddOtherElement_(key_value, this->m_root);
    }
    return {iter, size != this->m_size};
  }
};
