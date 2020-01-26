#include "test_runner.h"

#include <numeric>
#include <iostream>
#include <vector>
#include <string>
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
