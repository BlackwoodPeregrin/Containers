#pragma once

#include <iostream>

#include "../balance_tree/AvlTree.hpp"

template <class Key, class Value>
class Map : public AvlBalanceTree<Key, Value> {
 public:
  Map() : AvlBalanceTree<Key, Value>() {}
  Map(const Map &other) : AvlBalanceTree<Key, Value>(other) {}
  Map(const std::initializer_list<std::pair<Key, Value>> &items)
      : AvlBalanceTree<Key, Value>(items) {}
  Map(Map &&other) : AvlBalanceTree<Key, Value>(std::move(other)) {}
  ~Map() {}

  Map &operator=(const Map &other) {
    AvlBalanceTree<Key, Value>::operator=(other);
    return *this;
  }

  Map &operator=(Map &&other) {
    AvlBalanceTree<Key, Value>::operator=(std::move(other));
    return *this;
  }

  Value &at(const Key &key) {
    auto iter = this->Find(key);
    if (iter != this->end()) {
      return (*iter).second;
    }
    throw std::out_of_range("Tree::at");
  }

  Value &operator[](const Key &key) {
    std::pair<Key, Value> key_value(key, Value{});
    auto iter = this->Find(key);
    if (iter == this->end()) {
      iter = this->Insert(key_value).first;
    }
    return (*iter).second;
  }

  auto InsertOrAssign(const std::pair<Key, Value> &key_value) {
    auto result = this->Insert(key_value);
    if (result.second == false) {
      (*result.first).second = key_value.second;
    }
    return result;
  }

  auto InsertOrAssign(const Key &key, const Value &value) {
    std::pair<Key, Value> key_value(key, value);
    return InsertOrAssign(key_value);
  }
};
