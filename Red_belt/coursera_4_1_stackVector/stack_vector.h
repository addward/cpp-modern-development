#pragma once

#include <stdexcept>
#include <array>

using namespace std;

template <typename T, size_t N>
class StackVector {
public:
  explicit StackVector(size_t a_size = 0);

  T& operator[](size_t index);
  const T& operator[](size_t index) const;

  typename array<T, N>::iterator begin();
  typename array<T, N>::iterator end();
  typename array<T, N>::const_iterator begin() const;
  typename array<T, N>::const_iterator end() const;

  size_t Size() const;
  size_t Capacity() const;

  void PushBack(const T& value);
  T PopBack();

private:
    array<T, N> data_;
    size_t size_;
    size_t capacity_ = N;
};

template <typename T, size_t N>
StackVector<T, N>::StackVector(size_t a_size){
    if (a_size > N) throw invalid_argument("");
    size_ = a_size;
}

template <typename T, size_t N>
T& StackVector<T, N>::operator[](size_t index){
    return data_[index];
}

template <typename T, size_t N>
const T& StackVector<T, N>::operator[](size_t index) const{
    return data_[index];
}

template <typename T, size_t N>
typename array<T, N>::iterator StackVector<T, N>::begin(){
    return data_.begin();
}

template <typename T, size_t N>
typename array<T, N>::iterator StackVector<T, N>::end(){
    return next(data_.begin(), size_);
}

template <typename T, size_t N>
typename array<T, N>::const_iterator StackVector<T, N>::begin() const {
    return data_.begin();
}

template <typename T, size_t N>
typename array<T, N>::const_iterator   StackVector<T, N>::end() const {
    return next(data_.begin(), size_);
}

template <typename T, size_t N>
size_t StackVector<T, N>::Size() const{
    return size_;
}

template <typename T, size_t N>
size_t StackVector<T, N>::Capacity() const{
    return capacity_;
}

template <typename T, size_t N>
T StackVector<T, N>::PopBack(){
    if (size_ == 0) throw underflow_error("");
    --size_;
    return data_[size_];
}

template <typename T, size_t N>
void StackVector<T, N>::PushBack(const T& value){
    if (size_ == capacity_) throw overflow_error("");
    data_[size_] = value;
    ++size_;
}
