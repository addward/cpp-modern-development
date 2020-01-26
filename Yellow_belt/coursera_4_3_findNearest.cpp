#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

set<int>::const_iterator FindNearestElement(
    const set<int>& numbers,
    int border) {

    auto notGreaterIt = numbers.lower_bound(border);
    auto lowerIt      = notGreaterIt;

    if (end(numbers) == begin(numbers)){
            return end(numbers);
    }

    if (lowerIt == end(numbers)){
        return prev(end(numbers));
    }

    if (lowerIt != begin(numbers)){
        --lowerIt;
    }

    if (border - *lowerIt <= *notGreaterIt - border) {
        return lowerIt;
    } else {
        return notGreaterIt;
    }
}

int main() {

  set<int> numbers = {1, 2, 3,4,5,6,7,8,9,10,11};
  for (int i = 1; i < 300000; i++){
    numbers.insert(i);
  }
  cout <<
      *FindNearestElement(numbers, 3) << " " <<
      *FindNearestElement(numbers, 4) << " " <<
      *FindNearestElement(numbers, 5) << " " <<
      *FindNearestElement(numbers, 6) << " " <<
      *FindNearestElement(numbers, 7) << endl;

  set<int> empty_set;

  cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << endl;

  return 0;
}
