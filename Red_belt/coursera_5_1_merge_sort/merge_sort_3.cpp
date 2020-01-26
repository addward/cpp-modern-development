#include "test_runner.h"
#include <algorithm>
#include <memory>
#include <vector>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
  size_t size = range_end - range_begin;
  if (size < 2) return;

  vector tmp =
  vector<typename iterator_traits<RandomIt>::value_type>(move_iterator(range_begin), move_iterator(range_end));

  RandomIt first_end = begin(tmp) + size / 3;
  RandomIt second_end = begin(tmp) + 2 * size / 3;

  MergeSort(begin(tmp), first_end);
  MergeSort(first_end  , second_end);
  MergeSort(second_end , end(tmp));

  vector<typename iterator_traits<RandomIt>::value_type> tmp_two_parts;

  merge(move_iterator(begin(tmp)), move_iterator(first_end),
        move_iterator(first_end), move_iterator(second_end),
        back_inserter(tmp_two_parts));
  merge(move_iterator(begin(tmp_two_parts)), move_iterator(end(tmp_two_parts)),
        move_iterator(second_end), move_iterator(end(tmp)),
        range_begin);
}

void TestIntVector() {
  vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
  MergeSort(begin(numbers), end(numbers));
  ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {

  TestRunner tr;
  RUN_TEST(tr, TestIntVector);
  return 0;
}
