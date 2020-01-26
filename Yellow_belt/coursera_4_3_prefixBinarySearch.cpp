#include <iostream>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(
    RandomIt range_begin, RandomIt range_end,
    const string& prefix){
    size_t prefix_len = end(prefix) - begin(prefix);
    RandomIt ub = upper_bound(range_begin, range_end, prefix, [prefix_len](string prefix, string b){
                    size_t word_length = end(b) - begin(b);
                    //cout << prefix << " " << b << ": ";
                    if (word_length < prefix_len){
                        //cout << lexicographical_compare(begin(prefix), end(prefix), begin(b), end(b)) << endl;
                        return lexicographical_compare(begin(prefix), end(prefix), begin(b), end(b));
                    }
                    else{
                        return lexicographical_compare(begin(prefix), end(prefix), begin(b), begin(b) + prefix_len);
                    }
                });
    //cout << *ub << endl;
    RandomIt lb = lower_bound(range_begin, range_end, prefix, [prefix_len](string b, string prefix){
                    size_t word_length = end(b) - begin(b);
                    //cout << b << " " << prefix << ": ";
                    if (word_length < prefix_len){
                        return !lexicographical_compare(begin(prefix), end(prefix), begin(b), begin(b) + prefix_len);
                    }
                    else{
                        //cout << lexicographical_compare(begin(b), begin(b) + prefix_len, begin(prefix), end(prefix)) << endl;
                        return lexicographical_compare(begin(b), begin(b) + prefix_len, begin(prefix), end(prefix));
                        //return !lexicographical_compare(begin(prefix), end(prefix), begin(b), begin(b) + prefix_len);
                    }
                });
    //cout << *lb << endl;
    return {lb, ub};
}

int main() {
  const vector<string> sorted_strings = {"moscow", "motovilikha", "murmansk"};

  const auto mo_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), "mo");
  for (auto it = mo_result.first; it != mo_result.second; ++it) {
    cout << *it << " ";
  }
  cout << endl;
  cout << (mo_result.first - begin(sorted_strings)) << " " <<
      (mo_result.second - begin(sorted_strings)) << endl;

  const auto mt_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), "mt");
  cout << (mt_result.first - begin(sorted_strings)) << " " <<
      (mt_result.second - begin(sorted_strings)) << endl;

  const auto na_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), "na");
  cout << (na_result.first - begin(sorted_strings)) << " " <<
      (na_result.second - begin(sorted_strings)) << endl;

  return 0;
}

/*
#include <algorithm>
#include <utility>
#include <string>


template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(
	RandomIt range_begin, RandomIt range_end, string prefix) {

  // Все строки, начинающиеся с prefix, больше или равны строке "<prefix>"
  auto left = lower_bound(range_begin, range_end, prefix);

  // Составим строку, которая в рамках буквенных строк является
  // точной верхней гранью множества строк, начинающихся с prefix
  string upper_bound = prefix;
  ++upper_bound[upper_bound.size() - 1];

  // Первое встреченное слово, не меньшее upper_bound,
  // обязательно является концом полуинтервала
  auto right = lower_bound(range_begin, range_end, upper_bound);

  return {left, right};
}
*/
