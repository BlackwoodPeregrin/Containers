#include <limits>

template <typename T>
List<T>::List()
    : m_head(nullptr),
      m_tail(nullptr),
      m_begin(nullptr),
      m_end(nullptr),
      m_size(0) {
  m_end = new Node(T(), nullptr, nullptr);
  m_begin = m_end;
}

template <typename T>
List<T>::List(size_t n) : List<T>::List() {
  if (n >= max_size()) {
    throw std::invalid_argument("List:");
  }
  while (m_size != n) {
    push_back(T());
  }
}

template <typename T>
List<T>::List(std::initializer_list<T> const &items) : List<T>::List() {
  if (items.size() >= max_size()) {
    throw std::invalid_argument("List:");
  }
  for (const T &value : items) {
    push_back(value);
  }
}

template <typename T>
List<T>::List(const List<T> &l) : List<T>::List() {
  *this = l;
}

template <typename T>
List<T>::List(List<T> &&l) : List<T>::List() {
  *this = std::move(l);
}

template <typename T>
List<T>::~List() {
  clear();
  delete m_end;
}

template <typename T>
void List<T>::clear() {
  while (m_head != nullptr) {
    Node *cur = m_head;
    m_head = m_head->m_next;
    delete cur;
  }
  m_tail = nullptr;
  m_size = 0;

  m_end = new Node(T(), nullptr, nullptr);
  m_begin = m_end;
}

template <typename T>
List<T> &List<T>::operator=(const List &other) {
  if (this != &other) {
    clear();
    Node *cur = other.m_head;
    while (cur != nullptr && cur != other.m_end) {
      push_back(cur->m_data);
      cur = cur->m_next;
    }
  }
  return *this;
}

template <typename T>
List<T> &List<T>::operator=(List &&other) {
  if (this == &other) {
    throw std::out_of_range("List:");
  }
  clear();
  delete m_end;
  m_end = nullptr;
  swap(other);
  return *this;
}

template <typename T>
void List<T>::swap(List<T> &other) {
  if (this != &other) {
    std::swap(m_head, other.m_head);
    std::swap(m_tail, other.m_tail);
    std::swap(m_begin, other.m_begin);
    std::swap(m_end, other.m_end);
    std::swap(m_size, other.m_size);
  }
}

template <typename T>
const T &List<T>::front() {
  if (empty()) {
    throw std::out_of_range("front:");
  }
  return m_head->m_data;
}

template <typename T>
const T &List<T>::back() {
  if (empty()) {
    throw std::out_of_range("back:");
  }
  return m_tail->m_data;
}

template <typename T>
void List<T>::push_front(const T &value) {
  Push_(value, TypePushPop::kFront);
}

template <typename T>
void List<T>::push_back(const T &value) {
  Push_(value, TypePushPop::kBack);
}

template <typename T>
void List<T>::Push_(const T &value, bool type_push) {
  if (m_size == max_size()) {
    throw std::out_of_range("push:");
  }
  if (m_head == nullptr) {
    m_head = new Node(value, nullptr, m_end);
    m_tail = m_head;
    m_begin = m_head;
    m_end->m_prev = m_tail;
  } else {
    if (type_push == TypePushPop::kFront) {
      m_head->m_prev = new Node(value, nullptr, m_head);
      m_head = m_head->m_prev;
      m_begin = m_head;
    } else {
      m_tail->m_next = new Node(value, m_tail, m_end);
      m_tail = m_tail->m_next;
      m_end->m_prev = m_tail;
    }
  }
  ++m_size;
}

template <typename T>
T List<T>::pop_front() {
  return Pop_(TypePushPop::kFront);
}

template <typename T>
T List<T>::pop_back() {
  return Pop_(TypePushPop::kBack);
}

template <typename T>
T List<T>::Pop_(bool type_pop) {
  if (empty()) {
    throw std::out_of_range("Pop:");
  }
  --m_size;
  if (m_tail == m_head) {
    return PopLastElement_();
  } else {
    T value{};
    if (type_pop == TypePushPop::kFront) {
      value = m_head->m_data;
      m_head = m_head->m_next;
      delete m_head->m_prev;
      m_head->m_prev = nullptr;
      m_begin = m_head;
    } else {
      value = m_tail->m_data;
      m_tail = m_tail->m_prev;
      delete m_tail->m_next;
      m_tail->m_next = m_end;
      m_end->m_prev = m_tail;
    }
    return value;
  }
}

template <typename T>
T List<T>::PopLastElement_() {
  T value = m_head->m_data;
  delete m_head;
  m_head = nullptr;
  m_tail = nullptr;
  m_end->m_prev = nullptr;
  m_begin = m_end;
  return value;
}

template <typename T>
bool List<T>::equal(const List &other) {
  if (size() != other.size()) {
    return false;
  }
  Node *cur = m_head;
  Node *cur_other = other.m_head;
  while (cur != nullptr && cur_other != nullptr) {
    if (cur->m_data != cur_other->m_data) {
      return false;
    }
    cur = cur->m_next;
    cur_other = cur_other->m_next;
  }
  return true;
}

template <typename T>
bool List<T>::empty() const {
  return (m_size == 0);
}

template <typename T>
size_t List<T>::size() const {
  return m_size;
}

template <typename T>
size_t List<T>::max_size() const {
  return (std::numeric_limits<size_t>::max() /
          ((sizeof(Node) * 4) + sizeof(size_t)));
}

/*----------Iterator----------*/

template <typename T>
List<T>::Iterator::Iterator() : m_cur(nullptr) {}

template <typename T>
List<T>::Iterator::Iterator(const Iterator &other) : m_cur(nullptr) {
  *this = other;
}

template <typename T>
List<T>::Iterator::Iterator(Iterator &&other) : m_cur(nullptr) {
  *this = std::move(other);
}

template <typename T>
List<T>::Iterator::Iterator(Node *node) {
  m_cur = node;
}

template <typename T>
typename List<T>::Iterator &List<T>::Iterator::operator=(
    const Iterator &other) {
  m_cur = other.m_cur;
  return *this;
}

template <typename T>
typename List<T>::Iterator &List<T>::Iterator::operator=(Iterator &&other) {
  m_cur = nullptr;
  std::swap(m_cur, other.m_cur);
  return *this;
}

template <typename T>
typename List<T>::Iterator &List<T>::Iterator::operator++() {
  if (m_cur == nullptr) {
    throw std::out_of_range("operator++:");
  }
  if (m_cur->m_next != nullptr) {
    m_cur = m_cur->m_next;
  }
  return *this;
}

template <typename T>
typename List<T>::Iterator &List<T>::Iterator::operator--() {
  if (m_cur == nullptr) {
    throw std::out_of_range("operator--:");
  }
  if (m_cur->m_prev == nullptr) {
    while (m_cur->m_next != nullptr) {
      m_cur = m_cur->m_next;
    }
  } else {
    m_cur = m_cur->m_prev;
  }
  return *this;
}

template <typename T>
T &List<T>::Iterator::operator*() {
  if (m_cur == nullptr) {
    throw std::out_of_range("operator*:");
  }
  return m_cur->m_data;
}

template <typename T>
bool List<T>::Iterator::operator==(const Iterator &iter) {
  return (m_cur == iter.m_cur);
}

template <typename T>
bool List<T>::Iterator::operator!=(const Iterator &iter) {
  return (m_cur != iter.m_cur);
}

/*-------------------------------------------*/

template <typename T>
bool List<T>::erase(Iterator pos) {
  Node *current = m_head;
  Iterator iter = begin();

  while (iter != end()) {
    if (iter == pos) {
      break;
    }
    ++iter;
    current = current->m_next;
  }

  if (iter == end()) {
    return false;
  } else if (iter == begin()) {
    pop_front();
  } else if (iter == --end()) {
    pop_back();
  } else {
    current->m_prev->m_next = current->m_next;
    current->m_next->m_prev = current->m_prev;
    delete current;
    --m_size;
  }
  return true;
}

template <typename T>
typename List<T>::Iterator List<T>::insert(Iterator pos, const T &value) {
  if (m_size == max_size()) {
    throw std::invalid_argument("insert:");
  }

  if (pos == end()) {
    push_back(value);
    return --end();
  }

  Node *current = m_head;
  Iterator iter = begin();

  while (iter != end()) {
    if (iter == pos) {
      break;
    }
    ++iter;
    current = current->m_next;
  }

  if (iter == end()) {
    return end();
  } else if (iter == begin()) {
    push_front(value);
    return begin();
  } else {
    Node *new_node = new Node(value, current->m_prev, current);
    current->m_prev->m_next = new_node;
    current->m_prev = new_node;
    ++m_size;
    return Iterator(new_node);
  }
}

template <typename T>
void List<T>::splice(ConstIterator pos, List &other) {
  if (m_size + other.size() >= max_size()) {
    throw std::out_of_range("splice:");
  }

  if (this != &other) {
    if (pos == cend()) {
      m_tail->m_next = other.m_head;
      other.m_head->m_prev = m_tail;
      m_tail = other.m_tail;
      m_tail->m_next = m_end;
      m_end->m_prev = m_tail;
      //
      m_size += other.size();
      //
      other.m_head = nullptr;
      other.m_tail = nullptr;
      other.m_size = 0;
      other.m_end->m_prev = nullptr;
      other.m_begin = other.m_end;
    }

    ConstIterator iter = cbegin();
    Node *current = m_head;

    while (iter != cend()) {
      if (iter == pos) {
        break;
      }
      ++iter;
      current = current->m_next;
    }

    if (iter != cend()) {
      if (iter == cbegin()) {
        other.m_tail->m_next = m_head;
        m_head->m_prev = other.m_tail;
        m_head = other.m_head;
        m_begin = m_head;
      } else {
        current->m_prev->m_next = other.m_head;
        other.m_head->m_prev = current->m_prev;
        other.m_tail->m_next = current;
        current->m_prev = other.m_tail;
      }
      m_size += other.size();
      //
      other.m_head = nullptr;
      other.m_tail = nullptr;
      other.m_size = 0;
      other.m_end->m_prev = nullptr;
      other.m_begin = other.m_end;
    }
  }
}

template <typename T>
void List<T>::reverse() {
  if (empty()) {
    throw std::invalid_argument("reverse:");
  }
  List tmp;
  for (Iterator it = begin(); it != end(); ++it) {
    tmp.push_front(*it);
  }
  *this = std::move(tmp);
}

template <typename T>
void List<T>::sort() {
  if (empty()) {
    throw std::invalid_argument("sort:");
  }
  size_t tmp = size();
  for (size_t i = 0; i < tmp; i++) {
    Node *current = m_begin;
    for (size_t j = 0; j < tmp - i - 1; j++) {
      if (current->m_data > current->m_next->m_data) {
        std::swap(current->m_data, current->m_next->m_data);
      }
      current = current->m_next;
    }
  }
}

template <typename T>
void List<T>::unique() {
  Iterator it = begin();
  while (it != end()) {
    Iterator copy = it;
    ++copy;
    if (*it == *copy && copy != end()) {
      erase(it);
    }
    ++it;
  }
}
