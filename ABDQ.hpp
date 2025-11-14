#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* data_;                 // underlying dynamic array
    std::size_t capacity_;    // total allocated capacity
    std::size_t size_;        // number of stored elements
    std::size_t front_;       // index of front element
    std::size_t back_;        // index after the last element (circular)

    static constexpr std::size_t SCALE_FACTOR = 2;

public:
    // Big 5
    ABDQ() {
        capacity_ = 4;
        size_ = 0;
        front_ = 0;
        back_ = 0;
        data_ = new T[capacity_];
    }
    explicit ABDQ(std::size_t capacity) {
        capacity_ = capacity;
        size_ = 0;
        front_ = 0;
        back_ = 0;
        data_ = new T[capacity_];
    }
    ABDQ(const ABDQ& other) {
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;
        data_ = new T[capacity_];
        for (std::size_t i = 0; i < size_; i++) {
            data_[i] = other.data_[i];
        }
    }
    ABDQ(ABDQ&& other) noexcept {
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;
        data_ = other.data_;

        other.data_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;
    }
    ABDQ& operator=(const ABDQ& other) {
        if (this == &other) {
            return *this;
        }
        delete[] data_;
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;
        data_ = new T[capacity_];

        for (std::size_t i = 0; i < size_; i++) {
            data_[i] = other.data_[i];
        }
        return *this;
    }
    ABDQ& operator=(ABDQ&& other) noexcept {
        if (this == &other) {
            return *this;
        }
        delete[] data_;
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;
        data_ = other.data_;

        other.data_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;

        return *this;
    }
    ~ABDQ() override {
        delete[] data_;
        data_ = nullptr;
        capacity_ = 0;
        size_ = 0;
        front_ = 0;
        back_ = 0;
    }

    void ensureCapacity() {
        capacity_ *= 2;
    }
    void shrinkIfNeeded() {
        capacity_ /= 2;
    }

    // Insertion
    void pushFront(const T& item) override {
        if (size_ == capacity_) {
            ensureCapacity();
            T* new_data_ = new T[capacity_];
            for (int i = size_ - 1; i >= 0; i--) {
                new_data_[i+1] = data_[i];
            }
            delete[] data_;
            data_ = new_data_;
        }
        else {
            for (size_t i = size_; i > 0; i--) {
                data_[i] = data_[i - 1];
            }
        }
        data_[0] = item;
        size_++;
    }
    void pushBack(const T& item) override {
        if (size_ == capacity_) {
            ensureCapacity();
            T* new_array = new T[capacity_];
            for (size_t i = 0; i < size_; i++) {
                new_array[i] = data_[i];
            }
            delete[] data_;
            data_ = new_array;
        }
        data_[size_] = item;
        size_++;
    }

    // Deletion
    T popFront() override {
        if (size_ == 0) {
            throw std::runtime_error("empty ABS");
        }
        T data = data_[0];
        for (size_t i = 0; i < size_ - 1; i++) {
            data_[i] = data_[i + 1];
        }
        data_[size_ - 1] = T();
        size_--;
        if (size_ <= capacity_/4) {
            shrinkIfNeeded();
            T* new_array = new T[capacity_];
            for (size_t i = 0; i < size_; i++) {
                new_array[i] = data_[i];
            }
            delete[] data_;
            data_ = new_array;
        }
        return data;
    }
    T popBack() override {
        if (size_ == 0) {
            throw std::runtime_error("empty ABS");
        }
        T value = data_[size_ - 1];
        size_--;
        if (size_ <= capacity_/4) {
            shrinkIfNeeded();
            T* new_array = new T[capacity_];
            for (size_t i = 0; i < size_; i++) {
                new_array[i] = data_[i];
            }
            delete[] data_;
            data_ = new_array;
        }
        return value;
    }

    // Access
    const T& front() const override {
        if (size_ == 0) {
            throw std::runtime_error("empty ABS");
        }
        return data_[0];
    }
    const T& back() const override {
        if (size_ == 0) {
            throw std::runtime_error("empty ABS");
        }
        return data_[size_ - 1];
    }

    // Getters
    std::size_t getSize() const noexcept override {
        return size_;
    }

};
