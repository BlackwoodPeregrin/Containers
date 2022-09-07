template <typename T>
Queue<T>::Queue() : m_front(nullptr), m_back(nullptr), m_size(0) {}

template <typename T>
Queue<T>::Queue(std::initializer_list<T> const& items)
    : m_front(nullptr), m_back(nullptr), m_size(0) {
  for (const T& value : items) {
    Push(value);
  }
}

template <typename T>
Queue<T>::Queue(const Queue& q) : m_front(nullptr), m_back(nullptr), m_size(0) {
  *this = q;
}

template <typename T>
Queue<T>::Queue(Queue&& q) : m_front(nullptr), m_back(nullptr), m_size(0) {
  *this = std::move(q);
}

template <typename T>
void Queue<T>::clear() {
  while (m_front != nullptr) {
    Pop();
  }
  m_back = nullptr;
}

template <typename T>
Queue<T>::~Queue() {
  clear();
}

template <typename T>
Queue<T>& Queue<T>::operator=(const Queue& q) {
  if (this != &q) {
    clear();
    Node* current = q.m_front;
    while (current != nullptr) {
      Push(current->m_data);
      current = current->m_next;
    }
  }
  return *this;
}

template <typename T>
void Queue<T>::operator=(Queue&& q) {
  if (this == &q) {
    throw std::invalid_argument("operator=:");
  }
  clear();
  swap(q);
}

template <typename T>
const T& Queue<T>::Front() {
  if (IsEmpty()) {
    throw std::out_of_range("Front:");
  }
  return m_front->m_data;
}

template <typename T>
const T& Queue<T>::Back() {
  if (IsEmpty()) {
    throw std::out_of_range("Back:");
  }
  return m_back->m_data;
}

template <typename T>
bool Queue<T>::IsEmpty() {
  return (m_size == 0);
}

template <typename T>
size_t Queue<T>::Size() {
  return m_size;
}

template <typename T>
void Queue<T>::Push(const T& value) {
  if (m_front == nullptr) {
    m_front = new Node(value);
    m_back = m_front;
  } else {
    if (m_front == m_back) {
      m_back = new Node(value);
      m_front->m_next = m_back;
    } else {
      m_back->m_next = new Node(value);
      m_back = m_back->m_next;
    }
  }
  ++m_size;
}

template <typename T>
T Queue<T>::Pop() {
  if (IsEmpty()) {
    throw std::out_of_range("Pop:");
  }
  Node* toDel = m_front;
  T value = toDel->m_data;
  m_front = m_front->m_next;
  delete toDel;
  toDel = nullptr;
  --m_size;
  return value;
}

template <typename T>
void Queue<T>::swap(Queue& q) {
  std::swap(m_front, q.m_front);
  std::swap(m_back, q.m_back);
  std::swap(m_size, q.m_size);
}
