#include "test_runner.h"


#include <vector>
#include <future>
#include <numeric>
#include <algorithm>

using namespace std;

template <typename Iterator>
class Page{
public:
    Page(Iterator start, Iterator end) :
        _start(start),
        _end(end) {}

    Iterator end(){
        return _end;
    }

    const Iterator end() const {
        return _end;
    }

    Iterator begin(){
        return _start;
    }

    const Iterator begin() const {
        return _start;
    }

    size_t size() const{
        return (_end - _start);
    }
private:
    Iterator _start, _end;
};

template <typename Iterator>
class Paginator {
public:
    Paginator(Iterator begin, Iterator end, size_t page_size){
        Iterator page_end = begin;
        Iterator page_start = begin;
        while (page_end != end) {
            page_end = next(page_start, min(page_size, (size_t)(end - page_start)));
            _pages.push_back({page_start, page_end});
            page_start = page_end;
        }
        _page_size = _pages.size();
    }

    size_t size() const {
        return _page_size;
    }

    auto begin(){
        return _pages.begin();
    }

    auto begin() const {
        return _pages.begin();
    }

    auto end(){
        return _pages.end();
    }

    auto end() const {
        return _pages.end();
    }

private:
    vector<Page<Iterator>> _pages;
    size_t _page_size;
};

template <typename C>
auto Paginate(C& c, size_t page_size) {
  return Paginator(begin(c), end(c), page_size);
}

int64_t CalculateMatrixSum(const vector<vector<int>>& matrix) {
  Paginator a = Paginate(matrix, 2000);
  vector<future<int64_t>> futures;
  for (auto iter = a.begin(); iter != a.end(); ++iter) {
    futures.push_back(async([=]{
        int64_t sum = 0;
        for (auto veciter = iter->begin(); veciter != iter->end(); ++veciter) {
            sum += accumulate(veciter->begin(), veciter->end(), 0);
        }
        return sum;
        }));
  }
  int64_t sum = 0;
  for (auto futIter = futures.begin(); futIter != futures.end(); ++futIter) {
    sum += futIter->get();
  }
  return sum;
}

void TestCalculateMatrixSum() {
  const vector<vector<int>> matrix = {
    {1,  2,  3,  4},
    {5,  6,  7,  8},
    {9,  10, 11, 12},
    {13, 14, 15, 16}
  };
  ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestCalculateMatrixSum);
}
