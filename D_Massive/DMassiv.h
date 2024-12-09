// Copyright 2024 Kirill Remizov

#ifndef LIB_DMASSIVE_LIB_DMASSIVE_HEDER_H_
#define LIB_DMASSIVE_LIB_DMASSIVE_HEDER_H_

#pragma once
#define STEP_CAPACITY 15
#include <iostream>
#include <algorithm>
#include <utility>
#include "../lib_Algorithms/algoritms.h"

enum State { empty, busy, deleted };

template <typename T>
class DMassiv {
    T* _data;
    State* _states;
    size_t _capacity;
    size_t _size;
    size_t _deleted;

 public:
    DMassiv();
    DMassiv(const DMassiv& archive);
    DMassiv(const T* arr, size_t n);
    DMassiv(size_t n, T value);
    DMassiv(const DMassiv& archive, size_t pos, size_t len);

    ~DMassiv();

    void print() const noexcept;

    inline bool empty() const noexcept;
    inline bool full() const noexcept;

    size_t size() const;
    size_t capacity() const;
    const T* data() const;

    void swap(DMassiv& archive);

    void clear();
    void reserve(size_t n);
    void resize(size_t n, T value);
    void repack();
    void cleanDeleted();

    DMassiv& assign(const DMassiv& archive);

    void push_back(T value);
    void pop_back();
    void push_front(T value);
    void pop_front();

    DMassiv& insert(const T* arr, size_t n, size_t pos);
    DMassiv& insert(T value, size_t pos);

    DMassiv& replace(size_t pos, T new_value);

    DMassiv& remove_by_index(size_t pos);
    DMassiv& erase(size_t pos, size_t n);
    DMassiv& remove_all(T value);
    DMassiv& remove_first(T value);
    DMassiv& remove_last(T value);

    size_t& find_all(T value, const size_t& count) const noexcept;
    size_t find_first(T value) const;
    size_t find_last(T value) const;
    class Iterator {
    public:
        Iterator(T* ptr, State* states) : ptr(ptr), states(states) {}

        T& operator*() const {
            return *ptr;
        }

        Iterator& operator++() {
            do {
                ++ptr;
                ++states;
            } while (*states == State::deleted);
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return ptr != other.ptr;
        }

        bool operator==(const Iterator& other) const {
            return ptr == other.ptr;
        }

    private:
        T* ptr;
        State* states;
    };

    Iterator begin() {
        return Iterator(_data, _states);
    }

    Iterator end() {
        return Iterator(_data + _size, _states + _size);
    }
};

template <typename T>
DMassiv<T>::DMassiv() {
    _size = 0;
    _capacity = STEP_CAPACITY;
    _data = new T[_capacity];
    _states = new State[_capacity];
    for (size_t i = 0; i < STEP_CAPACITY; i++) {
        _states[i] = State::empty;
    }
}

template <typename T>
DMassiv<T>::DMassiv(const DMassiv& archive) {
    _capacity = archive._capacity;
    _size = archive._size;
    _deleted = archive._deleted;
    _states = new State[_capacity];
    _data = new T[_capacity];
    for (size_t i = 0; i < _capacity; i++) {
        _states[i] = archive._states[i];
    }
    for (int i = 0; i < _size; i++) {
        _data[i] = archive._data[i];
    }
}

template <typename T>
DMassiv<T>::DMassiv(const T* arr, size_t n) {
    _size = n;
    _capacity = (_size / STEP_CAPACITY) * STEP_CAPACITY + STEP_CAPACITY;
    _states = new State[_capacity];
    _data = new T[_capacity];
    _deleted = 0;
    for (size_t i = 0; i < _capacity; i++) {
        _states[i] = State::empty;
    }
    for (int i = 0; i < n; i++) {
        _data[i] = arr[i];
    }
    for (size_t i = 0; i < n; i++) {
        _states[i] = State::busy;
    }
}

template <typename T>
DMassiv<T>::DMassiv(size_t n, T value) {
    _size = n;
    _capacity = (_size / STEP_CAPACITY) * STEP_CAPACITY + STEP_CAPACITY;
    _states = new State[_capacity];
    _data = new T[_capacity];
    _deleted = 0;
    for (size_t i = 0; i < _capacity; i++) {
        _states[i] = State::empty;
    }
    for (int i = 0; i < n; i++) {
        _data[i] = value;
    }
    for (size_t i = 0; i < n; i++) {
        _states[i] = State::busy;
    }
}

template <typename T>
DMassiv<T>::DMassiv(const DMassiv& archive, size_t pos, size_t len) {
    _size = len;
    _capacity = (_size / STEP_CAPACITY) * STEP_CAPACITY + STEP_CAPACITY;
    _deleted = 0;
    _states = new State[_capacity];
    _data = new T[_capacity];
    for (size_t i = 0; i < _capacity; i++) {
        _states[i] = State::empty;
    }
    for (size_t i = 0; i < _size; i++) {
        _states[i] = State::busy;
    }
    for (int i = 0; i < _size; i++) {
        _data[i] = archive._data[i + pos];
    }
}

template <typename T>
DMassiv<T>::~DMassiv() {
    delete[] _data;
    _data = nullptr;
}

template <typename T>
inline bool DMassiv<T>::empty() const noexcept {
    return _size == 0;
}

template <typename T>
inline bool DMassiv<T>::full() const noexcept {
    return _size == _capacity;
}

template<typename T>
size_t DMassiv<T>::size() const {
    return _size;
}

template<typename T>
size_t DMassiv<T>::capacity() const {
    return _capacity;
}

template<typename T>
const T* DMassiv<T>::data() const {
    return _data;
}

template<typename T>
void DMassiv<T>::swap(DMassiv& archive) {
    for (int i = 0; i < algorithms::max(_size, archive._size); i++) {
        algorithms::swap(_data[i], archive._data[i]);
    }
}

template<typename T>
void DMassiv<T>::clear() {
    _data = nullptr;
    _states = nullptr;
    _size = 0;
    _deleted = 0;
    _capacity = STEP_CAPACITY;
}

template<typename T>
void DMassiv<T>::reserve(size_t n) {
    if (_capacity == -1) {
        std::cout << "Is Full" << '\n';
        return;
    } else {
        _capacity
            = ((_size + n) / STEP_CAPACITY) * STEP_CAPACITY + STEP_CAPACITY;
    }
    T* new_data;
    State* new_states;
    new_data = new T[_capacity];
    new_states = new State[_capacity];
    for (int i = 0; i < _size; i++) {
        new_data[i] = _data[i];
        new_states[i] = _states[i];
    }
    for (int i = _size; i < _capacity; i++) {
        new_states[i] = State::empty;
    }
    delete[] _data;
    delete[] _states;
    _data = new_data;
    _states = new_states;
}

template<typename T>
void DMassiv<T>::resize(size_t n, T value) {
    n -= 1;
    this->reserve(n);
    for (int i = _size - 1; i < _size + n; i++) {
        _data[i] = value;
    }
    for (int i = _size - 1; i < _size + n; i++) {
        _states[i] = State::busy;
    }
    _size += n;
}

template<typename T>
void DMassiv<T>::repack() {
    int j = 0;
    for (int i = 0; i < _size; i++) {
        if (_states[i] != State::deleted) {
            _data[j] = _data[i];
            _states[j] = _states[i];
            j++;
        }
    }
    _size = j;
}

template<typename T>
DMassiv<T>& DMassiv<T>::assign(const DMassiv& archive) {
    this->reserve(archive._size);
    for (int i = 0; i < archive._size; i++) {
        _data[i] = archive._data[i];
        _states[i] = State::busy;
    }
    for (int i = archive._size; i < _capacity; i++) {
        _states[i] = State::empty;
    }
    _size = archive._size;
    return *this;
}

template<typename T>
void DMassiv<T>::push_back(T value) {
    this->reserve(1);
    _data[_size] = value;
    _size += 1;
}

template<typename T>
void DMassiv<T>::pop_back() {
    _states[_size - 1] = State::empty;
    _size -= 1;
}

template<typename T>
void DMassiv<T>::push_front(T value) {
    this->reserve(1);
    for (int i = _size; i >= 0; i--) {
        _data[i + 1] = _data[i];
    }
    _data[0] = value;
    _size += 1;
}

template<typename T>
void DMassiv<T>::pop_front() {
    for (int i = 0; i < _size; i++) {
        if (_states[i] == busy) {
            _states[i] = deleted;
            _size -= 1;
            break;
        }
    }
}

template<typename T>
DMassiv<T>& DMassiv<T>::remove_by_index(size_t pos) {
    _states[pos] = State::deleted;
    _size -= 1;
    return *this;
}

template <typename T>
DMassiv<T>& DMassiv<T>::insert(T value, size_t pos) {
    if (_size < pos) {
        throw std::logic_error
        ("Error in function DMassiv<>&insert(T): wrong position value.");
    }

    this->reserve(1);

    for (size_t i = _size; i > pos; i--) {
        _data[i] = _data[i - 1];
    }
    _data[pos] = value;
    _states[pos] = State::busy;
    _size++;
    return *this;
}

template <typename T>
DMassiv<T>& DMassiv<T>::insert(const T* arr, size_t n, size_t pos)  {
    this->reserve(n);
    for (int i = _size - 1; i >= pos; i--) {
        _data[i + n] = _data[i];
    }
    for (int i = pos, j = 0; i < n + pos; i++, j++) {
        _data[i] = arr[j];
    }
    _size += n;
    return *this;
}

template <typename T>
DMassiv<T>& DMassiv<T>::replace(size_t pos, T new_value) {
    _data[pos] = new_value;
    return *this;
}

template <typename T>
void DMassiv<T>::print() const noexcept {
    for (size_t i = 0; i < _size; i++) {
        if (_states[i] != State::deleted) {
            std::cout << _data[i] << ", ";
        }
    }
    std::cout << '\n';
}

template <typename T>
DMassiv<T>& DMassiv<T>::erase(size_t pos, size_t n) {
    for (int i = pos; i < pos + n; i++) {
        _states[i] = State::deleted;
    }
    _size -= n;
    return *this;
}

template <typename T>
DMassiv<T>& DMassiv<T>::remove_all(T value) {
    int j = 0;
    for (int i = 0; i < _size; i++) {
        if (_data[i] == value) {
            _states[i] = State::deleted;
            j++;
        }
    }
    _size -= j;
    return *this;
}

template <typename T>
DMassiv<T>& DMassiv<T>::remove_first(T value) {
    for (int i = 0; i < value; i++) {
        _states[i] = State::deleted;
        break;
    }
    _size -= 1;
    return *this;
}

template <typename T>
DMassiv<T>& DMassiv<T>::remove_last(T value) {
    for (int i = _size - 1, j = 0; j < value; i--, j++) {
        _states[i] = State::deleted;
    }
    _size -= 1;
    return *this;
}

template <typename T>
size_t& DMassiv<T>::find_all(T value, const size_t& count) const noexcept {
    size_t* find_values;
    size_t _count = 0;
    for (int i = 0; i < _size; i++) {
        if (_data[i] == value) {
            _count++;
        }
    }
    find_values = new size_t[_count];
    count = _count;
    _count = 0;
    for (int i = 0; i < _size; i++) {
        if (_data[i] == value) {
            find_values[_count] = i;
            _count++;
        }
    }
    return *find_values;
}

template <typename T>
size_t DMassiv<T>::find_first(T value) const {
    for (int i = 0; i < _size; i++) {
        if (_data[i] == value) {
            return i;
        }
    }
    return -1;
}

template <typename T>
size_t DMassiv<T>::find_last(T value) const {
    for (int i = _size; i >= 0; i--) {
        if (_data[i] == value) {
            return i;
        }
    }
    return -1;
}

template <typename T>
void DMassiv<T>::cleanDeleted() {
    size_t j = 0;
    for (size_t i = 0; i < _size; ++i) {
        if (_states[i] != State::deleted) {
            _data[j] = _data[i];
            _states[j] = _states[i];
            ++j;
        }
    }
    _size = j;
}


#endif  // LIB_DMASSIVE_LIB_DMASSIVE_HEDER_H_
