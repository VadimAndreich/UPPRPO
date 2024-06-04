#include <iostream>
#include "CB.h"

template <typename valueType>
CircularBuffer<valueType>::CircularBuffer() : buffer(nullptr), size_(0), capacity_(0), begin_(0) {}

template <typename valueType>
CircularBuffer<valueType>::CircularBuffer(int capacity) : size_(0), capacity_(capacity), begin_(0) {
    buffer = new valueType[capacity];
}

template <typename valueType>
CircularBuffer<valueType>::CircularBuffer(int capacity, const valueType &elem) : size_(capacity), capacity_(capacity), begin_(0) {
    buffer = new valueType[capacity_];
    for (int i = 0; i < capacity; ++i) {
        buffer[i] = elem;
    }
}

template <typename valueType>
CircularBuffer<valueType>::CircularBuffer(const CircularBuffer &cb) noexcept {
    buffer = cb.buffer;
    capacity_ = cb.capacity_;
    size_ = cb.size_;
    begin_ = cb.begin_;
}

template <typename valueType>
CircularBuffer<valueType>::CircularBuffer(const CircularBuffer &&cb) noexcept : buffer(nullptr), capacity_(0), size_(0), begin_(0) {
    buffer = cb.buffer;
    capacity_ = cb.capacity_;
    size_ = cb.size_;
    begin_ = cb.begin_;

    cb.buffer = nullptr;
}

template <typename valueType>
CircularBuffer<valueType>::~CircularBuffer() {
    free(buffer);
}

template <typename valueType>
valueType &CircularBuffer<valueType>::operator[](int i) {
    return buffer[(begin_ + i) % capacity_];
}

template <typename valueType>
const valueType &CircularBuffer<valueType>::operator[](int i) const {
    return buffer[(begin_ + i) % capacity_];
}

template <typename valueType>
valueType &CircularBuffer<valueType>::at(int i) {
    if (i < 0 || i >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return buffer[(begin_ + i) % capacity_];
}

template <typename valueType>
const valueType &CircularBuffer<valueType>::at(int i) const {
    if (i < 0 || i >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return buffer[(begin_ + i) % capacity_];
}


template <typename valueType>
valueType &CircularBuffer<valueType>::front() {
    if (size_ == 0) {
        throw std::out_of_range("Buffer is empty");
    }
    return buffer[begin_];
}

template <typename valueType>
valueType &CircularBuffer<valueType>::back() {
    if (size_ == 0) {
        throw std::out_of_range("Buffer is empty");
    }
    return buffer[(begin_ + size_ - 1) % capacity_];
}

template <typename valueType>
const valueType &CircularBuffer<valueType>::front() const {
    if (size_ == 0) {
        throw std::out_of_range("Buffer is empty");
    }
    return buffer[begin_];
}

template <typename valueType>
const valueType &CircularBuffer<valueType>::back() const {
    if (size_ == 0) {
        throw std::out_of_range("Buffer is empty");
    }
    return buffer[(begin_ + size_ - 1) % capacity_];
}

template <typename valueType>
valueType* CircularBuffer<valueType>::linearize() {
    if (is_linearized()) {
        return buffer;
    } else {
            valueType* new_buffer [capacity_];
        for (int i = 0; i < size_; ++i) {
            new_buffer[i] = buffer[(begin_ + i) % capacity_];
        }
        std::copy(std::begin(new_buffer), std::end(new_buffer), std::begin(buffer));
        free(new_buffer);
        begin_ = 0;
        return buffer;
    }
}

template <typename valueType>
bool CircularBuffer<valueType>:: is_linearized() const {
    return (begin_ == 0);
}

template <typename valueType>
void CircularBuffer<valueType>::rotate(int new_begin) {
    if (new_begin < 0 || new_begin >= size_) {
        throw std::out_of_range("New begin index out of range");
    }
    begin_ = (begin_ + new_begin) % capacity_;
}

template <typename valueType>
int CircularBuffer<valueType>::size() const {
    return size_;
}

template <typename valueType>
bool CircularBuffer<valueType>::empty() const {
    return size_ == 0;
}

template <typename valueType>
bool CircularBuffer<valueType>::full() const {
    return size_ == capacity_;
}

template <typename valueType>
int CircularBuffer<valueType>::reserve() const {
    return capacity_ - size_;
}

template <typename valueType>
int CircularBuffer<valueType>::capacity() const {
    return capacity_;
}

template <typename valueType>
void CircularBuffer<valueType>::set_capacity(int new_capacity) {
    if (new_capacity < size_) {
        throw std::invalid_argument("New capacity is too small");
    }
    valueType* new_buffer;
    new_buffer = new valueType[new_capacity];
    for (int i = 0; i < size_; i++) {
        new_buffer[i] = buffer[(begin_ + i) % capacity_];
    }

    buffer = new_buffer;
    free(new_buffer);
    capacity_ = new_capacity;
    begin_ = 0;
}

template <typename valueType>
void CircularBuffer<valueType>::resize(int new_size, const valueType &item) {
    if (new_size < 0) {
        throw std::invalid_argument("New size cannot be negative");
    }
    if (new_size > capacity_) {
        set_capacity(new_size);
        while (size_ < new_size) {
            push_back(item);
        }
    }
    else {
        while (size_ > new_size) {
            pop_back();
        }
    }
}

template <typename valueType>
CircularBuffer<valueType> &CircularBuffer<valueType>::operator=(const CircularBuffer &cb) {
    if (this == &cb) {
        return *this;
    }
    free(buffer);
    capacity_ = cb.capacity_;
    size_ = cb.size_;
    begin_ = 0;
    buffer = new valueType[cb.capacity_];
    for (int i = 0; i < size_; ++i) {
        buffer[i] = cb.buffer[(cb.begin_ + i) % cb.capacity_];
    }
    return *this;
}

template <typename valueType>
CircularBuffer<valueType> &CircularBuffer<valueType>::operator=(CircularBuffer<valueType> &&cb) noexcept {
    free(buffer);
    capacity_ = cb.capacity_;
    size_ = cb.size_;
    begin_ = cb.begin_;
    buffer = cb.buffer;

    cb.buffer = nullptr;
    return *this;
}

template <typename valueType>
void CircularBuffer<valueType>::swap(CircularBuffer &cb) {
    std::swap(size_, cb.size_);
    std::swap(capacity_, cb.capacity_);
    std::swap(begin_, cb.begin_);
    std::swap(buffer, cb.buffer);
}

template <typename valueType>
void CircularBuffer<valueType>::push_back(const valueType &item) {
    if (full()) {
        buffer[begin_] = item;
        begin_ = (begin_ + 1) % capacity_;
    } else {
        buffer[(begin_ + size_) % capacity_] = item;
        size_ = std::min(size_ + 1, capacity_);
    }
}

template <typename valueType>
void CircularBuffer<valueType>::push_front(const valueType &item) {
    if (full()) {
        begin_ = (begin_ - 1 + capacity_) % capacity_;
        buffer[begin_] = item;
    } else {
        begin_ = (begin_ - 1 + capacity_) % capacity_;
        buffer[begin_] = item;
        size_ = std::min(size_ + 1, capacity_);
    }
}

template <typename valueType>
void CircularBuffer<valueType>::pop_back() {
    if (empty()) {
        throw std::out_of_range("Buffer is empty");
    }
    size_--;
}

template <typename valueType>
void CircularBuffer<valueType>::pop_front() {
    if (empty()) {
        throw std::out_of_range("Buffer is empty");
    }
    begin_ = (begin_ + 1) % capacity_;
    size_--;
}

template <typename valueType>
void CircularBuffer<valueType>::insert(int pos, const valueType &item) {
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

template <typename valueType>
void CircularBuffer<valueType>::erase(int first, int last) {
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

template <typename valueType>
void CircularBuffer<valueType>::clear() {
    size_ = 0;
    begin_ = 0;
}

template <typename valueType>
bool operator==(const CircularBuffer<valueType> &a, const CircularBuffer<valueType> &b) {
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

template <typename valueType>
bool operator!=(const CircularBuffer<valueType> &a, const CircularBuffer<valueType> &b) {
    return !(a == b);
}
