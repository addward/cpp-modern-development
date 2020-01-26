#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end){
    if (range_end - range_begin == 1)
        return;
    RandomIt it_one_third = range_begin + (range_end - range_begin)/3;
    RandomIt it_two_third = range_begin + 2*(range_end - range_begin)/3;

    vector<typename RandomIt::value_type> first_vec(range_begin, it_one_third);
    vector<typename RandomIt::value_type> sec_vec(it_one_third, it_two_third);
    vector<typename RandomIt::value_type> third_vec(it_two_third, range_end);

    MergeSort(begin(first_vec), end(first_vec));
    MergeSort(begin(sec_vec), end(sec_vec));
    MergeSort(begin(third_vec), end(third_vec));

    vector<typename RandomIt::value_type> temp_vec;
    merge(begin(first_vec), end(first_vec), begin(sec_vec), end(sec_vec), back_inserter(temp_vec));
    merge(begin(temp_vec), end(temp_vec), begin(third_vec), end(third_vec), range_begin);
}

int main() {
  vector<int> v = {0};
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

  // 3. Разбиваем вектор на три равные части
  auto one_third = elements.begin() + range_length / 3;
  auto two_third = elements.begin() + range_length * 2 / 3;

  // 4. Вызываем функцию MergeSort от каждой трети вектора
  MergeSort(elements.begin(), one_third);
  MergeSort(one_third, two_third);
  MergeSort(two_third, elements.end());

  // 5. С помощью алгоритма merge cливаем первые две трети во временный вектор
  // back_inserter -> http://ru.cppreference.com/w/cpp/iterator/back_inserter
  vector<typename RandomIt::value_type> interim_result;
  merge(elements.begin(), one_third, one_third, two_third,
        back_inserter(interim_result));

  // 6. С помощью алгоритма merge сливаем отсортированные части
  // в исходный диапазон
  // merge -> http://ru.cppreference.com/w/cpp/algorithm/merge
  merge(interim_result.begin(), interim_result.end(), two_third, elements.end(),
        range_begin);
}
*/
