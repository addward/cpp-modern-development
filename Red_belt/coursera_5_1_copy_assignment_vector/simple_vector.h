#pragma once

#include <cstdlib>
#include <algorithm>
#include <iostream>

using namespace std;

// Реализуйте шаблон SimpleVector
template <typename T>
class SimpleVector {
public:
  SimpleVector();
  explicit SimpleVector(size_t size);
  ~SimpleVector();
  SimpleVector& operator=(const SimpleVector& other);

  T& operator[](size_t index);

  T* end();
  T* begin();
  const T* begin() const;
  const T* end() const;

  size_t Size()     const;
  size_t Capacity() const;
  void   PushBack(const T& value);

private:
  size_t capacity_;
  void   allocate(size_t size);
  T* beginPtr_;
  T* endPtr_;
};

template <typename T>
void SimpleVector<T>::allocate(size_t size){
    if (beginPtr_ != nullptr) {
        delete[] beginPtr_;
    }
    beginPtr_ = new T[size];
    endPtr_ = beginPtr_;
    capacity_ = size;
}

template <typename T>
void SimpleVector<T>::PushBack(const T& value){
    if (capacity_ == 0) {
        allocate(1);
        *beginPtr_ = value;
        endPtr_ = beginPtr_ + 1;
        return;
    }
    if (endPtr_ == beginPtr_ + capacity_) {
        size_t tmpSize = capacity_;
        T* tmp = new T[tmpSize * 2];
        copy(beginPtr_, endPtr_, tmp);

        //allocate(capacity_ * 2);
        //copy(tmp, tmp + tmpSize, beginPtr_);
        delete[] beginPtr_;
        beginPtr_ = tmp;
        capacity_ = 2 * tmpSize;

        beginPtr_[tmpSize] = value;
        endPtr_ = beginPtr_ + tmpSize + 1;

        return;
    }
    *endPtr_ = value;
    ++endPtr_;
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
    /*
    if (rhs.size <= capacity) {
      // У нас достаточно памяти - просто копируем элементы
      copy(rhs.begin(), rhs.end(), begin());
      size = rhs.size;
    } else {
      // Это так называемая идиома copy-and-swap.
      // Мы создаём временный вектор с помощью
      // конструктора копирования, а затем обмениваем его поля со своими.
      // Так мы достигаем двух целей:
      //  - избегаем дублирования кода в конструкторе копирования
      //    и операторе присваивания
      //  - обеспечиваем согласованное поведение конструктора копирования
      //    и оператора присваивания
      SimpleVector<T> tmp(rhs);
      swap(tmp.data, data);
      swap(tmp.size, size);
      swap(tmp.capacity, capacity);
    }
    */
}

template <typename T>
SimpleVector<T>& SimpleVector<T>::operator=(const SimpleVector<T>& other){
    allocate(other.Capacity());
    copy(other.begin(), other.end(), beginPtr_);
    endPtr_ = beginPtr_ + other.Size();
    return *this;
}
