#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

class RouteManager {
public:
  void AddRoute(int start, int finish) {
    reachable_lists_[start].insert(finish);
    reachable_lists_[finish].insert(start);
  }
  int FindNearestFinish(int start, int finish) const {
    int result = abs(start - finish);
    if (reachable_lists_.count(start) < 1) {
        return result;
    }
    const set<int>& reachable_stations = reachable_lists_.at(start);
    if (!reachable_stations.empty()) {
      /*result = min(
          result,
          abs(finish - *min_element(
              begin(reachable_stations), end(reachable_stations),
              [finish](int lhs, int rhs) { return abs(lhs - finish) < abs(rhs - finish); }
          ))
      );*/
      auto lbIterator = reachable_stations.lower_bound(finish);

      vector<int> distances{result};

      // Insert distance to the lowerBound if it exists
      if (lbIterator != end(reachable_stations)){
        distances.push_back(abs(*(lbIterator) - finish));

        // Insert distance to the next station from lowerBound if it exists
        if (next(lbIterator) != end(reachable_stations)){
            distances.push_back(abs(*next(lbIterator) - finish));
        }
      }

      // Insert distance to the previous station from lowerBound if it exists
      if (lbIterator != begin(reachable_stations)){
        distances.push_back(abs(*prev(lbIterator) - finish));
      }

      result = *(min_element(begin(distances), end(distances)));
    }
    return result;
  }
private:
  //map<int, vector<int>> reachable_lists_;
  map<int, set<int>> reachable_lists_;
};


int main() {
  RouteManager routes;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;
    int start, finish;
    cin >> start >> finish;
    if (query_type == "ADD") {
      routes.AddRoute(start, finish);
    } else if (query_type == "GO") {
      cout << routes.FindNearestFinish(start, finish) << "\n";
    }
  }

  return 0;
}
