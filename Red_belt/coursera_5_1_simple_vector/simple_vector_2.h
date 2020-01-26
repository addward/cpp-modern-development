#pragma once

#include <cstdint>
#include <cstdlib>
#include <algorithm>
#include <iostream>

using namespace std;

// Реализуйте SimpleVector в этом файле
// и отправьте его на проверку

template <typename T>
class SimpleVector {
public:
  SimpleVector();// = default;
  explicit SimpleVector(size_t size);
  ~SimpleVector();

  T& operator[](size_t index);

  T* begin();
  T* end();
  const T* begin() const;
  const T* end() const;

  size_t Size() const;
  size_t Capacity() const;
  void PushBack(const T value);

  // При необходимости перегрузите
  // существующие публичные методы

private:
  size_t capacity_;
  void   allocate(size_t size);
  T* beginPtr_;
  T* endPtr_;
};


template <typename T>
void SimpleVector<T>::PushBack(T value){
    if (capacity_ == 0) {
        allocate(1);
        *beginPtr_ = move(value);
        endPtr_ = beginPtr_ + 1;
        return;
    }
    if (endPtr_ == beginPtr_ + capacity_) {
        size_t tmpSize = capacity_;
        T* tmp = new T[tmpSize * 2];
        move(beginPtr_, endPtr_, tmp);

        //allocate(capacity_ * 2);
        //copy(tmp, tmp + tmpSize, beginPtr_);
        delete[] beginPtr_;
        beginPtr_ = tmp;
        capacity_ = 2 * tmpSize;

        beginPtr_[tmpSize] = move(value);
        endPtr_ = beginPtr_ + tmpSize + 1;

        return;
    }
    *endPtr_ = move(value);
    ++endPtr_;
}

template <typename T>
T& SimpleVector<T>::operator[](size_t index){
    if (index > capacity_ - 1) throw out_of_range("");
    return beginPtr_[index];
}

template <typename T>
SimpleVector<T>::~SimpleVector(){
    if (beginPtr_ != nullptr) delete[] beginPtr_;
}

template <typename T>
SimpleVector<T>::SimpleVector() {
    capacity_ = 0;
    beginPtr_ = nullptr;
    endPtr_   = nullptr;
}

template <typename T>
SimpleVector<T>::SimpleVector(size_t size){
    if (size == 0) {
        capacity_ = 0;
        beginPtr_ = nullptr;
        endPtr_   = nullptr;
        return;
    }
    capacity_  = size;
    T* heapMem = new T[size];
    beginPtr_  = heapMem;
    endPtr_    = heapMem + size;
}

template <typename T>
T* SimpleVector<T>::begin(){
    return beginPtr_;
}

template <typename T>
T* SimpleVector<T>::end(){
    return endPtr_;
}

template <typename T>
const T* SimpleVector<T>::begin() const {
    return beginPtr_;
}

template <typename T>
const T* SimpleVector<T>::end() const {
    return endPtr_;
}


template <typename T>
size_t SimpleVector<T>::Capacity() const {
    return capacity_;
}

template <typename T>
size_t SimpleVector<T>::Size() const {
    return endPtr_ - beginPtr_;
}

template <typename T>
void SimpleVector<T>::allocate(size_t size){
    if (beginPtr_ != nullptr) {
        delete[] beginPtr_;
    }
    beginPtr_ = new T[size];
    endPtr_ = beginPtr_;
    capacity_ = size;
}
