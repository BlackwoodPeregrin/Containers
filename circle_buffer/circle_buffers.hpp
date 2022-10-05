#include <iostream>

// condition - логическое условие
// TypeIfTrue - тип возвращаемый, если условие истинно,
// TypeIfFale - тип возвращаемый, если условие ложно,

template <bool Condition, class TypeIfTrue, class TypeIfFale>
struct StaticIf {
  typedef TypeIfTrue Result;
};

template <class TypeIfTrue, class TypeIfFale>
struct StaticIf<false, TypeIfTrue, TypeIfFale> {
  typedef TypeIfFale Result;
};

template <unsigned SIZE>
struct SelectTypeForIndexBuffer {
  static const bool kLessOrEqUint8T{SIZE <= 0xff};
  static const bool kLessOrEqUint16T{SIZE <= 0xffff};
  typedef
      // поместится в 8 бит - вернем uint8_t
      typename StaticIf<kLessOrEqUint8T, uint8_t,
                        // поместится в 16 бит - вернём - uint16_t, иначе
                        // uint32_t
                        typename StaticIf<kLessOrEqUint16T, uint16_t,
                                          uint32_t>::Result>::Result ResultType;
};

// Шаблон кольцевого буфера
// принимает два параметра:
// размер буфера - должен быть степенью двойки,
// тип элементов хранящихся в буфере

/*============================================================================================*/

template <unsigned SIZE, class DATA_T>
class CircleBufferStaticMemory {
  /*---Проверка, чтобы размер буфера был степенью двойки, в обратном случае
  static_assert выкенет строковый литерал, который поступает вторым
  параметром---*/
  static_assert((SIZE & (SIZE - 1)) == 0, "Size buffer must be degree of 2");

 public:
  // тип для индексов зависит от входячего значения SIZE
  typedef typename SelectTypeForIndexBuffer<SIZE>::ResultType INDEX_T;

  // запись в буфер, возвращает true если значение записано
  inline bool Write(DATA_T value) {
    if (IsFull()) {
      return false;
    }
    m_data[m_write_count++ & m_mask] = value;
    return true;
  }
  // чтение из буфера, возвращает true если значение прочитано
  inline bool Read(DATA_T& value) {
    if (IsEmpty()) {
      return false;
    }
    value = m_data[m_read_count++ & m_mask];
    return true;
  }
  // возвращает первый элемент из буфера, не удаляя его
  inline DATA_T First() const {
    if (IsEmpty()) {
      throw std::out_of_range("First:");
    }
    return operator[](0);
  }
  // возвращает последний элемент из буфера, не удаляя его
  inline DATA_T Last() const {
    if (IsEmpty()) {
      throw std::out_of_range("Last:");
    }
    return operator[](Size() - 1);
  }
  // возвращает элемент по индексу
  inline DATA_T& operator[](INDEX_T i) {
    if (i >= Size()) {
      throw std::out_of_range("operator[]:");
    }
    return m_data[(m_read_count + i) & m_mask];
  }

  inline DATA_T operator[](INDEX_T i) const {
    if (i >= Size()) {
      throw std::out_of_range("operator[]:");
    }
    return m_data[(m_read_count + i) & m_mask];
  }
  // пуст ли буфер
  inline bool IsEmpty() const { return m_write_count == m_read_count; }
  // полон ли буфер
  inline bool IsFull() const {
    return ((INDEX_T)(m_write_count - m_read_count) & (INDEX_T) ~(m_mask)) != 0;
  }
  // количество элементов в буфере
  inline INDEX_T Size() const {
    if (m_write_count - m_read_count == SIZE) {
      return SIZE;
    }
    return (m_write_count - m_read_count) & m_mask;
  }

  // фактический размер буфера
  inline unsigned Capacity() const { return SIZE; }

  // очистить буфер
  inline void Clear() {
    m_read_count = 0;
    m_write_count = 0;
  }

 private:
  // память под буфер
  DATA_T m_data[SIZE];
  // количество чтений
  volatile INDEX_T m_read_count{0};
  // количество записей
  volatile INDEX_T m_write_count{0};
  // маска для индексов
  static const INDEX_T m_mask{SIZE - 1};
};

/*============================================================================================*/

template <unsigned SIZE, class DATA_T>
class CircleBufferDinamicMemory {
 private:
  /*---Проверка, чтобы размер буфера был >= 1---*/
  static_assert((SIZE != 0), "Size buffer must be degree of 2");
  // тип для индексов зависит от входячего значения SIZE
  typedef typename SelectTypeForIndexBuffer<SIZE>::ResultType INDEX_T;
  //
  class Node {
   public:
    Node(DATA_T value, Node* next, Node* prev)
        : m_value(value), m_next(next), m_prev(prev) {}

    DATA_T m_value;
    Node* m_next;
    Node* m_prev;
  };

 public:
  class Iterator {
   public:
    Iterator(Iterator const& other) { *this = other; }
    Iterator(Node* node, Node* fake = nullptr) : m_current(node) {}
    ~Iterator() = default;

    Iterator& operator=(Iterator const& other) {
      m_current = other.m_current;
      return *this;
    }

    bool operator==(Iterator const& other) const {
      return (m_current == other.m_current);
    }

    bool operator!=(Iterator const& other) const {
      return !(operator==(other));
    }

    Iterator& operator++() {
      Increment_();
      return *this;
    }

    Iterator operator++(int) {
      Iterator copy(*this);
      Increment_();
      return copy;
    }

    Iterator& operator--() {
      Decrement_();
      return *this;
    }

    Iterator operator--(int) {
      Iterator copy(*this);
      Decrement_();
      return copy;
    }

    DATA_T& operator*() { return m_current->m_value; }

   protected:
    void Increment_() { m_current = m_current->m_next; }
    void Decrement_() { m_current = m_current->m_prev; }

    Node* m_current;
  };

  class ConstIterator : public Iterator {
   public:
    ConstIterator(ConstIterator const& other) : Iterator(other) {}
    ConstIterator(Node* node) : Iterator(node) {}
    ~ConstIterator() = default;
    DATA_T operator*() { return this->m_current->m_value; }
  };

 public:
  CircleBufferDinamicMemory() : m_write(nullptr), m_read(nullptr), m_size(0) {}

  CircleBufferDinamicMemory(CircleBufferDinamicMemory const& other)
      : CircleBufferDinamicMemory() {
    *this = other;
  }

  CircleBufferDinamicMemory(CircleBufferDinamicMemory&& other)
      : CircleBufferDinamicMemory() {
    *this = std::move(other);
  }

  CircleBufferDinamicMemory& operator=(CircleBufferDinamicMemory const& other) {
    if (this != &other) {
      Clear();
      for (int i = 0; i < other.m_size; ++i) {
        Write(other[i]);
      }
    }
    return *this;
  }

  CircleBufferDinamicMemory& operator=(CircleBufferDinamicMemory&& other) {
    if (this != &other) {
      Clear();
      std::swap(m_write, other.m_write);
      std::swap(m_read, other.m_read);
      std::swap(m_size, other.m_size);
    }
    return *this;
  }

  ~CircleBufferDinamicMemory() { Clear(); }

  // очистить буфер
  inline void Clear() {
    while (!IsEmpty()) {
      DATA_T value{};
      Read(value);
    }
  }

  Iterator Begin() {
    if (IsEmpty()) {
      throw std::out_of_range("Begin:");
    }
    return Iterator(m_read);
  }

  ConstIterator Cbegin() {
    if (IsEmpty()) {
      throw std::out_of_range("Cbegin:");
    }
    return ConstIterator(m_read);
  }

  // запись в буфер, возвращает true если значение записано
  inline bool Write(DATA_T value) {
    if (m_write == nullptr) {
      m_write = new Node(value, m_write, m_write);
      m_read = m_write;
    } else {
      if (IsFull()) {
        return false;
      }
      m_write->m_next = new Node(value, m_read, m_write);
      m_read->m_prev = m_write->m_next;
      m_write = m_write->m_next;
    }
    ++m_size;
    return true;
  }

  // чтение из буфера, возвращает true если значение прочитано
  inline bool Read(DATA_T& value) {
    if (m_read == nullptr) {
      return false;
    }
    value = m_read->m_value;
    Node* del = m_read;
    // в буфере лежит единственный не прочитанный элемент
    if (m_read == m_write) {
      m_read = nullptr;
      m_write = nullptr;
    } else {
      m_read = m_read->m_next;
      m_write->m_next = m_read;
      m_read->m_prev = m_write;
    }
    delete del;
    --m_size;
    return true;
  }

  // возвращает первый элемент из буфера, не удаляя его
  inline DATA_T First() const {
    if (IsEmpty()) {
      throw std::out_of_range("First:");
    }
    return m_read->m_value;
  }

  // возвращает последний элемент из буфера, не удаляя его
  inline DATA_T Last() const {
    if (IsEmpty()) {
      throw std::out_of_range("Last:");
    }
    return m_write->m_value;
  }

  // возвращает элемент по индексу
  inline DATA_T& operator[](INDEX_T i) {
    if (i >= m_size) {
      throw std::out_of_range("operator[]:");
    }
    Node* search_element{};
    // идем слева на право по буферу
    if (i < (m_size / 2)) {
      search_element = m_read;
      for (INDEX_T index = 0; index != i; ++index) {
        search_element = search_element->m_next;
      }
      // идем спарва на лево по буферу
    } else {
      search_element = m_write;
      for (INDEX_T index = m_size - 1; index != i; --index) {
        search_element = search_element->m_prev;
      }
    }
    return search_element->m_value;
  }

  inline DATA_T operator[](INDEX_T i) const {
    if (i >= m_size) {
      throw std::out_of_range("operator[]:");
    }
    DATA_T value{};
    // m_mutex.lock();
    Node* search_element{};
    // идем слева на право по буферу
    if (i < (m_size / 2)) {
      search_element = m_read;
      for (INDEX_T index = 0; index != i; ++index) {
        search_element = search_element->m_next;
      }
      // идем справа на лево по буферу
    } else {
      search_element = m_write;
      for (INDEX_T index = m_size - 1; index != i; --index) {
        search_element = search_element->m_prev;
      }
    }
    value = search_element->m_value;
    // m_mutex.unlock();
    return value;
  }

  // количество элементов в буфере
  inline INDEX_T Size() const { return m_size; }
  // фактический размер буфера
  inline unsigned Capacity() const { return SIZE; }

  // полон ли буфер
  inline bool IsFull() const { return m_size == SIZE; }
  // пуст ли буфер
  inline bool IsEmpty() const { return (m_size == 0); }

 private:
  Node* m_write;
  Node* m_read;
  INDEX_T m_size;
};

// // + читаемость
// // - скорость
// bool isEven(int value){return value%2==0;}

// // - читаемость
// // + скорость
// bool isEven(int value) { return ((value & 1) == 0); }

// // Побитовые операции выигрывают в производительности, но при этом их
// использование чуть-чуть усложняет читаемость кода
