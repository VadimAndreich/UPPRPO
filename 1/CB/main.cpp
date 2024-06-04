#include <iostream>
#include "lib/CB.cpp"

/*template <typename valueType>
class CircularBuffer {
private:
    valueType *buffer;
    int size_;
    int capacity_;
    int begin_;

public:
    CircularBuffer() : buffer(nullptr), size_(0), capacity_(0), begin_(0) {}

    explicit CircularBuffer(int capacity) : size_(0), capacity_(capacity), begin_(0) {
        buffer = new valueType[capacity];
    }

    CircularBuffer(int capacity, const valueType &elem) : CircularBuffer(capacity) {
        for (int i = 0; i < capacity; ++i) {
            buffer[i] = elem;
        }
        size_ = capacity;
    }

    CircularBuffer(const CircularBuffer &cb) : CircularBuffer(cb.capacity_) {
        size_ = cb.size_;
        for (int i = 0; i < size_; ++i) {
            buffer[i] = cb.buffer[(cb.begin_ + i) % cb.capacity_];
        }
    }

    ~CircularBuffer() {
        delete[] buffer;
    }

    valueType &operator[](int i) {
        return buffer[(begin_ + i) % capacity_];
    }

    const valueType &operator[](int i) const {
        return buffer[(begin_ + i) % capacity_];
    }

    valueType &at(int i) {
        if (i < 0 || i >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return buffer[(begin_ + i) % capacity_];
    }

    const valueType &at(int i) const {
        if (i < 0 || i >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return buffer[(begin_ + i) % capacity_];
    }

    valueType &front() {
        if (size_ == 0) {
            throw std::out_of_range("Buffer is empty");
        }
        return buffer[begin_];
    }

    valueType &back() {
        if (size_ == 0) {
            throw std::out_of_range("Buffer is empty");
        }
        return buffer[(begin_ + size_ - 1) % capacity_];
    }

    const valueType &front() const {
        if (size_ == 0) {
            throw std::out_of_range("Buffer is empty");
        }
        return buffer[begin_];
    }

    const valueType &back() const {
        if (size_ == 0) {
            throw std::out_of_range("Buffer is empty");
        }
        return buffer[(begin_ + size_ - 1) % capacity_];
    }

    valueType *linearize() {
        if (is_linearized()) {
            return buffer;
        } else {
            valueType *new_buffer = new valueType[capacity_];
//            valueType *new_buffer [capacity_];
            for (int i = 0; i < size_; ++i) {
                new_buffer[i] = buffer[(begin_ + i) % capacity_];
            }
            delete[] buffer;
            buffer = new_buffer;
            begin_ = 0;
            return buffer;
        }
    }

    bool is_linearized() const {
        return (begin_ == 0);
    }

    void rotate(int new_begin) {
        if (new_begin < 0 || new_begin >= size_) {
            throw std::out_of_range("New begin index out of range");
        }
        begin_ = (begin_ + new_begin) % capacity_;
    }

    int size() const {
        return size_;
    }

    bool empty() const {
        return size_ == 0;
    }

    bool full() const {
        return size_ == capacity_;
    }

    int reserve() const {
        return capacity_ - size_;
    }

    int capacity() const {
        return capacity_;
    }

    void set_capacity(int new_capacity) {
        if (new_capacity < size_) {
            throw std::invalid_argument("New capacity is too small");
        }
//        valueType *new_buffer = new valueType[new_capacity];
        valueType *new_buffer[new_capacity];
        for (int i = 0; i < size_; ++i) {
            new_buffer[i] = buffer[(begin_ + i) % capacity_];
        }
        delete[] buffer;
        buffer = new_buffer;
        capacity_ = new_capacity;
        begin_ = 0;
    }

    void resize(int new_size, const valueType &item = valueType()) {
        if (new_size < 0) {
            throw std::invalid_argument("New size cannot be negative");
        }
        if (new_size > capacity_) {
            set_capacity(new_size);
        }
        while (size_ < new_size) {
            push_back(item);
        }
        while (size_ > new_size) {
            pop_back();
        }
    }

    CircularBuffer &operator=(const CircularBuffer &cb) {
        if (this == &cb) {
            return *this;
        }
        delete[] buffer;
        capacity_ = cb.capacity_;
        size_ = cb.size_;
        begin_ = 0;
        buffer = new valueType[capacity_];
        for (int i = 0; i < size_; ++i) {
            buffer[i] = cb.buffer[(cb.begin_ + i) % cb.capacity_];
        }
        return *this;
    }

    void swap(CircularBuffer &cb) {
        std::swap(buffer, cb.buffer);
        std::swap(size_, cb.size_);
        std::swap(capacity_, cb.capacity_);
        std::swap(begin_, cb.begin_);
    }

    void push_back(const valueType &item = valueType()) {
        if (full()) {
            buffer[begin_] = item;
            begin_ = (begin_ + 1) % capacity_;
        }
        buffer[(begin_ + size_) % capacity_] = item;
        size_ = std::min(size_ + 1, capacity_);
    }

    void push_front(const valueType &item = valueType()) {
        if (full()) {
            begin_ = (begin_ - 1 + capacity_) % capacity_;
        }
        begin_ = (begin_ - 1 + capacity_) % capacity_;
        buffer[begin_] = item;
        size_ = std::min(size_ + 1, capacity_);
    }

    void pop_back() {
        if (empty()) {
            throw std::out_of_range("Buffer is empty");
        }
        size_--;
    }

    void pop_front() {
        if (empty()) {
            throw std::out_of_range("Buffer is empty");
        }
        begin_ = (begin_ + 1) % capacity_;
        size_--;
    }

    void insert(int pos, const valueType &item = valueType()) {
        if (pos < 0 || pos > size_) {
            throw std::out_of_range("Insert position is out of range");
        } else {
            for (int i = size_; i > pos; --i) {
                buffer[(begin_ + i) % capacity_] = buffer[(begin_ + i - 1) % capacity_];
            }
            buffer[(begin_ + pos) % capacity_] = item;

            if (!full()) { size_++; }
        }
    }

    void erase(int first, int last) {
        if (first > capacity_ || last > capacity_) {
            throw std::out_of_range("Index out of range");
        } else if (first < 0 || last < first || first == last || last > size_) {
            throw std::out_of_range("Erase range is invalid");
        }
        int num_to_move = size_ - last - 1;
        for (int i = 0; i < num_to_move; i++) {
            buffer[(begin_ + first + i) % capacity_] = buffer[(begin_ + last + i) % capacity_];
        }
        size_ -= (last - first + 1);
    }

    void clear() {
        size_ = 0;
        begin_ = 0;
    }
};

template <typename T>
bool operator==(const CircularBuffer<T> &a, const CircularBuffer<T> &b) {
    if (a.size() != b.size()) {
        return false;
    }
    for (int i = 0; i < a.size(); i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

template <typename T>
bool operator!=(const CircularBuffer<T> &a, const CircularBuffer<T> &b) {
    return !(a == b);
}

template <typename T>
void printArr(const CircularBuffer<T> &a)
{
    for (int i = 0; i < a.capacity(); i++) {
        std::cout << a[i] << " | ";
    }
    std::cout << std::endl;
}*/


int main()
{
    /*CircularBuffer<int> a(3, 1);
    CircularBuffer<int> b(a);
    for (int i = 0; i < b.size(); i++) {
        std::cout << b[i] << "  ";
    }*/

    return 0;
}