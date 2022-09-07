template <class T>
Vector<T>::Vector() : m_buffer(nullptr), m_capacity(1), m_size(0) {}

template <class T>
Vector<T>::Vector(size_t n) : m_capacity(n), m_size(n) {
  if (n > max_size()) {
    throw std::invalid_argument("Vector:");
  }
  m_buffer = new T[m_size]();
}

template <class T>
Vector<T>::Vector(const std::initializer_list<T> &items)
    : m_capacity(items.size()), m_size(items.size()) {
  if (items.size() > max_size()) {
    throw std::invalid_argument("Vector:");
  }
  m_buffer = new T[m_size]();
  iterator iter = begin();
  for (const T &value : items) {
    *iter = value;
    ++iter;
  }
}

template <class T>
Vector<T>::Vector(const Vector &v) : Vector() {
  *this = v;
}

template <class T>
Vector<T>::Vector(Vector &&v) : Vector() {
  *this = std::move(v);
}

template <class T>
Vector<T>::~Vector() {
  clear();
}

template <class T>
void Vector<T>::clear() {
  if (m_buffer != nullptr) {
    delete[] m_buffer;
  }
  m_buffer = nullptr;
  m_size = 0;
  m_capacity = 0;
}

template <class T>
Vector<T> &Vector<T>::operator=(const Vector &v) {
  if (this != &v) {
    clear();
    m_size = v.m_size;
    m_buffer = new T[m_size]();
    for (int i = 0; i < m_size; i++) {
      m_buffer[i] = v.m_buffer[i];
    }
    m_capacity = v.m_capacity;
  }
  return *this;
}

template <class T>
Vector<T> &Vector<T>::operator=(Vector &&v) {
  if (this == &v) {
    throw std::invalid_argument("operator=:");
  }

  clear();
  swap(v);
  return *this;
}

template <class T>
bool Vector<T>::empty() {
  return m_size == 0;
}

template <class T>
size_t Vector<T>::size() {
  return m_size;
}

template <class T>
size_t Vector<T>::capacity() {
  return m_capacity;
}

template <class T>
size_t Vector<T>::max_size() {
  return std::numeric_limits<size_t>::max() / (sizeof(this));
}

template <class T>
const T &Vector<T>::front() {
  if (empty()) {
    throw std::out_of_range("front:");
  }
  return m_buffer[0];
}

template <class T>
const T &Vector<T>::back() {
  if (empty()) {
    throw std::out_of_range("back:");
  }
  if (m_size == 0) {
    return m_buffer[0];
  } else {
    return m_buffer[m_size - 1];
  }
}

template <class T>
T &Vector<T>::operator[](size_t pos) {
  if (pos > max_size()) {
    throw std::out_of_range("operator[]:");
  }
  if (pos >= m_capacity) {
    _Redistribution(pos);
  }
  return m_buffer[pos];
}

template <class T>
T &Vector<T>::at(size_t pos) {
  if (pos >= m_size) {
    throw std::out_of_range("at:");
  }
  return m_buffer[pos];
}

template <class T>
typename Vector<T>::iterator Vector<T>::begin() {
  return m_buffer;
}

template <class T>
typename Vector<T>::iterator Vector<T>::end() {
  return &m_buffer[m_size];
}

template <class T>
typename Vector<T>::iterator Vector<T>::insert(iterator pos, const T &value) {
  if (m_size == max_size() || pos == nullptr) {
    throw std::invalid_argument("insert:");
  }

  iterator iter{};
  if (m_size == m_capacity) {
    _Redistribution(m_capacity * 2, pos);
  }
  T *buf = new T[m_capacity]();
  for (size_t i = 0, j = 0; i < m_size; ++i, j++) {
    if (pos == &m_buffer[i]) {
      buf[j] = value;
      iter = &buf[j];
      ++j;
    }
    buf[j] = m_buffer[i];
  }
  ++m_size;
  delete[] m_buffer;
  m_buffer = buf;
  return iter;
}

template <class T>
void Vector<T>::erase(const_iterator pos) {
  if (empty() || pos == nullptr) {
    throw std::out_of_range("erase:");
  }
  for (size_t i = pos - begin(); i < m_size; ++i) {
    m_buffer[i] = m_buffer[i + 1];
  }
  --m_size;
}

template <class T>
void Vector<T>::push_back(const T &value) {
  if (m_size == max_size()) {
    throw std::out_of_range("push_back:");
  }
  if (m_size == 0) {
    m_buffer = new T[m_capacity];
  }
  if (m_size == m_capacity) {
    _Redistribution2x();
  }
  m_buffer[m_size] = value;
  ++m_size;
}

template <class T>
void Vector<T>::pop_back() {
  if (empty()) {
    throw std::out_of_range("pop_back:");
  }
  --m_size;
}

template <class T>
void Vector<T>::swap(Vector &other) {
  if (this != &other) {
    std::swap(m_buffer, other.m_buffer);
    std::swap(m_size, other.m_size);
    std::swap(m_capacity, other.m_capacity);
  }
}

template <class T>
void Vector<T>::_Redistribution2x() {
  m_capacity *= 2;
  T *buf = new T[m_capacity]();
  for (int i = 0; i < m_size; i++) {
    buf[i] = m_buffer[i];
  }
  delete[] m_buffer;
  m_buffer = buf;
}

template <class T>
void Vector<T>::_Redistribution(size_t size) {
  m_capacity = size;
  if (m_size > m_capacity) {
    m_size = m_capacity;
  }
  T *buf = new T[m_capacity]();
  for (int i = 0; i < m_size; i++) {
    buf[i] = m_buffer[i];
  }
  delete[] m_buffer;
  m_buffer = buf;
  buf = nullptr;
}

template <class T>
void Vector<T>::_Redistribution(size_t newm_size, iterator &iter) {
  m_capacity = newm_size;
  T *buf = new T[m_capacity]();
  for (int i = 0; i < m_size; i++) {
    buf[i] = m_buffer[i];
    if (iter == &m_buffer[i]) {
      iter = &buf[i];
    }
  }
  delete[] m_buffer;
  m_buffer = buf;
  buf = nullptr;
}
