#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>

template <class T>
class ObjectPool {
public:
  T* Allocate();
  T* TryAllocate();

  void Deallocate(T* object);

  ~ObjectPool();

private:
  set<T*> allocated;
  vector<T*> deallocated;
};

template <class T>
ObjectPool<T>::~ObjectPool(){
    for (auto i = begin(allocated); i != end(allocated); ++i){
        delete *i;
    }
    for (auto i = begin(deallocated); i != end(deallocated); ++i){
        delete *i;
    }
}

template <class T>
T* ObjectPool<T>::Allocate(){
    T* element;
    if (deallocated.empty()){
        element = new T;
        allocated.insert(element);
    } else {
        element = *deallocated.begin();
        allocated.insert(element);
        deallocated.erase(deallocated.begin());
    }
    return element;
}

template <class T>
T* ObjectPool<T>::TryAllocate(){
    T* element;
    if (deallocated.empty()){
        element = nullptr;
    } else {
        element = *deallocated.begin();
        allocated.insert(element);
        deallocated.erase(deallocated.begin());
    }
    return element;
}

template <class T>
void ObjectPool<T>::Deallocate(T* object){
    auto it = allocated.find(object);
    if (it != end(allocated)) {
        deallocated.push_back(*it);
        allocated.erase(it);
    } else {
        throw invalid_argument("The argument is invalid");
    }
}

void TestObjectPool() {
  ObjectPool<string> pool;

  auto p1 = pool.Allocate();
  auto p2 = pool.Allocate();
  auto p3 = pool.Allocate();

  *p1 = "first";
  *p2 = "second";
  *p3 = "third";

  pool.Deallocate(p2);
  ASSERT_EQUAL(*pool.Allocate(), "second");

  pool.Deallocate(p3);
  pool.Deallocate(p1);
  ASSERT_EQUAL(*pool.Allocate(), "third");
  ASSERT_EQUAL(*pool.Allocate(), "first");

  pool.Deallocate(p1);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestObjectPool);
  return 0;
}
