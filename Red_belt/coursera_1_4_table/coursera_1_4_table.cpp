#include "test_runner.h"

using namespace std;

template <typename T>
class Table{
public:
    Table(size_t r, size_t c): _columns(c), _rows(r){
        _data = vector<vector<T>>(_rows, vector<T>(_columns));
    }
    pair<size_t, size_t> Size() const {
        return {_rows, _columns};
    }

    vector<T>& operator[](size_t pos){
        return _data[pos];
    }

    const vector<T>& operator[](size_t pos) const {
        return _data[pos];
    }

    void Resize(size_t r, size_t c){
        if (r != _rows) {
            _data.resize(r);
            _rows = r;
        }
        if (c != _columns) {
            for (auto& row : _data){
                row.resize(c);
            }
            _columns = c;
        }
    }
private:
    size_t _rows, _columns;
    vector<vector<T>> _data;
};

void TestTable() {
  Table<int> t(1, 1);
  ASSERT_EQUAL(t.Size().first, 1u);
  ASSERT_EQUAL(t.Size().second, 1u);
  t[0][0] = 42;
  ASSERT_EQUAL(t[0][0], 42);
  t.Resize(3, 4);
  ASSERT_EQUAL(t.Size().first, 3u);
  ASSERT_EQUAL(t.Size().second, 4u);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestTable);
  return 0;
}
