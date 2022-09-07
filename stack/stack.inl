template <typename T>
Stack<T>::Stack() : m_head(nullptr), m_size(0) {}

template <typename T>
Stack<T>::Stack(std::initializer_list<T> const& items)
    : m_head(nullptr), m_size(0) {
  for (const T& value : items) {
    Push(value);
  }
}

template <typename T>
Stack<T>::Stack(const Stack& s) : m_head(nullptr), m_size(0) {
  *this = s;
}

template <typename T>
Stack<T>::Stack(Stack&& s) : m_head(nullptr), m_size(0) {
  *this = std::move(s);
}

template <typename T>
Stack<T>::~Stack() {
  Clear();
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack& s) {
  if (this != &s) {
    Clear();
    Stack tmp;
    Node* current = s.m_head;
    while (current != nullptr) {
      tmp.Push(current->m_data);
      current = current->m_next;
    }
    while (!tmp.IsEmpty()) {
      Push(tmp.Pop());
    }
  }
  return *this;
}

template <typename T>
Stack<T>& Stack<T>::operator=(Stack&& s) {
  if (this == &s) {
    throw std::invalid_argument("operator=:");
  }
  Clear();
  Swap(s);
  return *this;
}

template <typename T>
const T& Stack<T>::Top() {
  if (IsEmpty()) {
    throw std::out_of_range("Top:");
  }
  return m_head->m_data;
}

template <typename T>
bool Stack<T>::IsEmpty() {
  return (m_size == 0);
}

template <typename T>
size_t Stack<T>::Size() {
  return m_size;
}

template <typename T>
void Stack<T>::Push(const T& value) {
  if (m_head == nullptr) {
    m_head = new Node(value);
  } else {
    Node* new_head = new Node(value, m_head);
    m_head = new_head;
  }
  m_size++;
}

template <typename T>
T Stack<T>::Pop() {
  if (IsEmpty()) {
    throw std::out_of_range("pop:");
  }
  Node* del = m_head;
  T value = del->m_data;
  m_head = m_head->m_next;
  delete del;
  --m_size;
  return value;
}

template <typename T>
void Stack<T>::Swap(Stack& other) {
  if (this != &other) {
    std::swap(m_head, other.m_head);
    std::swap(m_size, other.m_size);
  }
}

template <typename T>
void Stack<T>::Clear() {
  while (m_head != nullptr) {
    Pop();
  }
}
