#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>

using namespace std;

template <typename T>
class PriorityCollection {
public:
  using Id = size_t/* тип, используемый для идентификаторов */;

  // Добавить объект с нулевым приоритетом
  // с помощью перемещения и вернуть его идентификатор
  Id Add(T object);

  // Добавить все элементы диапазона [range_begin, range_end)
  // с помощью перемещения, записав выданные им идентификаторы
  // в диапазон [ids_begin, ...)
  template <typename ObjInputIt, typename IdOutputIt>
  void Add(ObjInputIt range_begin, ObjInputIt range_end,
           IdOutputIt ids_begin);

  // Определить, принадлежит ли идентификатор какому-либо
  // хранящемуся в контейнере объекту
  bool IsValid(Id id) const;

  // Получить объект по идентификатору
  const T& Get(Id id) const;

  // Увеличить приоритет объекта на 1
  void Promote(Id id);

  // Получить объект с максимальным приоритетом и его приоритет
  pair<const T&, int> GetMax() const;

  // Аналогично GetMax, но удаляет элемент из контейнера
  pair<T, int> PopMax();

private:
  Id lastId = 0;
  Id findMaxElement() const;
  map<Id, T>   collection;
  map<Id, int> priority;
};

using Id = size_t;

template<typename T>
Id PriorityCollection<T>::Add(T object) {
    collection[lastId] = move(object);
    priority[lastId] = 0;
    return lastId++;
}
template <typename T>
template <typename ObjInputIt, typename IdOutputIt>
void PriorityCollection<T>::Add(ObjInputIt range_begin, ObjInputIt range_end,
           IdOutputIt ids_begin) {
    while(range_begin != range_end) {
        collection[lastId] = move(*(range_begin++));
        priority  [lastId] = 0;
        *(ids_begin++) = lastId++;
    }
}

template <typename T>
bool PriorityCollection<T>::IsValid(Id id) const{
    return collection.count(id);
}

template <typename T>
const T& PriorityCollection<T>::Get(Id id) const {
    return collection.at(id);
}

template <typename T>
void PriorityCollection<T>::Promote(Id id) {
    if (IsValid(id)) {
        priority[id] += 1;
    }
}

template <typename T>
Id PriorityCollection<T>::findMaxElement() const{
    auto itMaxElem = max_element(rbegin(priority), rend(priority), [](const pair<Id, int> &lhs, const pair<Id, int> &rhs) {
                                                                                        return (lhs.second < rhs. second);
                                                                                      });
    return itMaxElem->first;
}

template <typename T>
pair<const T&, int> PriorityCollection<T>::GetMax() const {
    //Id max_id = prev(priority.end())->first;
    //return {collection.at(max_id), prev(end(priority))->second};
    Id maxId = findMaxElement();
    return {collection.at(maxId), priority.at(maxId)};
}
template <typename T>
pair<T, int> PriorityCollection<T>::PopMax() {
    //Id max_id = prev(priority.end())->first;
    //pair<T, int> tmp_pair = make_pair(move(collection.at(max_id)), prev(end(priority))->second);
    //priority.erase(prev(priority.end()));
    //collection.erase(prev(collection.end()));
    //return tmp_pair;
    Id maxId = findMaxElement();
    pair<T, int> tmp_pair = make_pair(move(collection.at(maxId)), priority.at(maxId));
    priority.erase(maxId);
    collection.erase(maxId);
    return tmp_pair;
}

class StringNonCopyable : public string {
public:
  using string::string;  // Позволяет использовать конструкторы строки
  StringNonCopyable(const StringNonCopyable&) = delete;
  StringNonCopyable(StringNonCopyable&&) = default;
  StringNonCopyable& operator=(const StringNonCopyable&) = delete;
  StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
  PriorityCollection<StringNonCopyable> strings;
  const auto white_id = strings.Add("white");
  const auto yellow_id = strings.Add("yellow");
  const auto red_id = strings.Add("red");

  strings.Promote(yellow_id);
  for (int i = 0; i < 2; ++i) {
    strings.Promote(red_id);
  }
  strings.Promote(yellow_id);
  {
      ASSERT(strings.IsValid(red_id));
      ASSERT(strings.IsValid(yellow_id));
      ASSERT(strings.IsValid(white_id));
  }
  {
      AssertEqual(strings.Get(red_id), "red");
      AssertEqual(strings.Get(white_id), "white");
      AssertEqual(strings.Get(yellow_id), "yellow");
  }
  {
    const auto item = strings.GetMax();
    ASSERT_EQUAL(item.first, "red");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "red");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "yellow");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "white");
    ASSERT_EQUAL(item.second, 0);
  }
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestNoCopy);
  return 0;
}
