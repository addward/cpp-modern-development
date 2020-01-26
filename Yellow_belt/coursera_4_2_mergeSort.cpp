#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end){
    if (range_end - range_begin == 1)
        return;
    vector<typename RandomIt::value_type> left_vec(range_begin, range_begin + (range_end - range_begin)/2);
    MergeSort(begin(left_vec), end(left_vec));
    vector<typename RandomIt::value_type> right_vec(range_begin + (range_end - range_begin)/2, range_end);
    MergeSort(begin(right_vec), end(right_vec));
    merge(begin(left_vec), end(left_vec), begin(right_vec), end(right_vec), range_begin);
}

int main() {
  vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1};
  MergeSort(begin(v), end(v));
  for (int x : v) {
    cout << x << " ";
  }
  cout << endl;
  return 0;
}

/*
template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
  // 1. Если диапазон содержит меньше 2 элементов, выходим из функции
  int range_length = range_end - range_begin;
  if (range_length < 2) {
    return;
  }

  // 2. Создаем вектор, содержащий все элементы текущего диапазона
  vector<typename RandomIt::value_type> elements(range_begin, range_end);

  // 3. Разбиваем вектор на две равные части
  auto mid = elements.begin() + range_length / 2;

  // 4. Вызываем функцию MergeSort от каждой половины вектора
  MergeSort(elements.begin(), mid);
  MergeSort(mid, elements.end());

  // 5. С помощью алгоритма merge сливаем отсортированные половины
  // в исходный диапазон
  // merge -> http://ru.cppreference.com/w/cpp/algorithm/merge
  merge(elements.begin(), mid, mid, elements.end(), range_begin);
}
*/
