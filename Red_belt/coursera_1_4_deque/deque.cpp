#include <vector>
#include <stdexcept>
#include <iostream>

using namespace std;

template <typename T>
class Deque{
public:
    bool Empty() const {
        return (_forw.empty() && _back.empty());
    }
    size_t Size() const {
        return (_forw.size() + _back.size());
    }
    T& operator[](size_t index){
        if (index > _forw.size() + _back.size() - 1 || this->Empty())
            throw out_of_range("indexOutOfRange");
        else {
            if (index >= _forw.size()){
                return _back[index - _forw.size()];
            } else {
                return *(end(_forw) - index - 1);
            }
        }
    }

    const T& operator[](size_t index) const {
        if (index > _forw.size() + _back.size() - 1 || this->Empty())
            throw out_of_range("indexOutOfRange");
        else {
            if (index >= _forw.size()){
                return _back[index - _forw.size()];
            } else {
                return *(end(_forw) - index - 1);
            }
        }
    }

    const T& At(size_t index) const {
        return this->operator[](index);
    }

    T& At(size_t index) {
        return this->operator[](index);
    }

    T& Front() {
        return this->At(0);
    }

    const T& Front() const {
        return this->At(0);
    }

    T& Back() {
        size_t last_index = _forw.size() + _back.size();
        return this->At(last_index - 1);
    }

    const T& Back() const {
        size_t last_index = _forw.size() + _back.size();
        return this->At(last_index - 1);
    }

    void PushFront(const T& elem) {
        _forw.push_back(elem);
    }

    void PushBack(const T& elem) {
        _back.push_back(elem);
    }
private:
    vector<T> _forw;
    vector<T> _back;
};

int main(){
    Deque<double> a;
    /*a.PushBack(4.0);
    a.PushFront(3.0);
    a.PushFront(2.0);
    */
    cout << a.Back() << endl;
}

