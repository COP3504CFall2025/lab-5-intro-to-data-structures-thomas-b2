#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <utility>



template <typename T>
class LLDQ : public DequeInterface<T> {
private:
    LinkedList<T> list;

public:
    // Constructor
    LLDQ();

    // Core Insertion Operations
    void pushFront(const T& item) override;
    void pushBack(const T& item) override;

    // Core Removal Operations
    T popFront() override;
    T popBack() override;

    // Element Accessors
    const T& front() const override;
    const T& back() const override;

    // Getter
    std::size_t getSize() const noexcept override;
};

template<typename T>
void LLDQ<T>::pushFront(const T& item) {
    list.addHead(item);
}

template<typename T>
void LLDQ<T>::pushBack(const T& item) {
    list.addTail(item);
}

template<typename T>
T LLDQ<T>::popFront() {
    if (list.getHead()) {
        T data = list.getHead()->data;
        list.removeHead();
        return data;
    }
    throw std::runtime_error("empty yoogit not allowed");
}

template<typename T>
T LLDQ<T>::popBack() {
    if (list.getHead()) {
        T data = list.getTail()->data;
        list.removeTail();
        return data;
    }
    throw std::runtime_error("empty yoogit not allowed");
}

template<typename T>
const T& LLDQ<T>::front() const {
    if (list.getHead()) {
        return list.getHead()->data;
    }
    throw std::runtime_error("empty yoogit not allowed");
}

template<typename T>
const T& LLDQ<T>::back() const {
    if (list.getHead()) {
        return list.getTail()->data;
    }
    throw std::runtime_error("empty yoogit not allowed");
}

template<typename T>
std::size_t LLDQ<T>::getSize() const noexcept {
    return list.getCount();
}








