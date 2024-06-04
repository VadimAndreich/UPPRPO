#ifndef __CIR_BUF__
#define __CIR_BUF__

template <typename valueType>
class CircularBuffer {
private:
    valueType *buffer;
    int size_;
    int capacity_;
    int begin_;

public:
    CircularBuffer();
    explicit CircularBuffer(int capacity);
    CircularBuffer(int capacity, const valueType &elem);
    CircularBuffer(const CircularBuffer &cb) noexcept;
    CircularBuffer(const CircularBuffer &&cb) noexcept;
    ~CircularBuffer();

    valueType &operator[](int i);
    const valueType &operator[](int i) const;
    valueType &at(int i);
    const valueType &at(int i) const;

    valueType &front();
    valueType &back();
    const valueType &front() const;
    const valueType &back() const;

    valueType *linearize();
    bool is_linearized() const;
    void rotate(int new_begin);
    int size() const;
    bool empty() const;
    bool full() const;
    int reserve() const;
    int capacity() const;
    void set_capacity(int new_capacity);
    void resize(int new_size, const valueType &item = valueType());

    CircularBuffer &operator=(const CircularBuffer &cb);
    CircularBuffer &operator=(CircularBuffer &&cb) noexcept;
    void swap(CircularBuffer &cb);
    void push_back(const valueType &item = valueType());
    void push_front(const valueType &item = valueType());
    void pop_back();
    void pop_front();
    void insert(int pos, const valueType &item = valueType());
    void erase(int first, int last);
    void clear();
};

template <typename T>
bool operator==(const CircularBuffer<T> &a, const CircularBuffer<T> &b);

template <typename T>
bool operator!=(const CircularBuffer<T> &a, const CircularBuffer<T> &b);


#endif