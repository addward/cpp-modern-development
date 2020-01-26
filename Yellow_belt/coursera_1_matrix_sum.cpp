#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;

class Matrix{
public:

    Matrix() : col(0), row(0){
        m = vector<vector<int>>(0,vector<int>(0,0));
    }

    Matrix(int num_rows, int num_cols) : col(num_cols), row(num_rows){
        Reset(num_rows, num_cols);
    }

    void Reset(int num_rows, int num_cols){
        col = num_cols;
        row = num_rows;
        if (num_rows < 0 || num_cols < 0){
            throw(out_of_range("Error: c,r = " + to_string(col) + ", " + to_string(row)));
        }
        if (col == 0 || row == 0)
            return;
        m.assign(row,vector<int>(col));
    }

    int At(int row_num, int col_num) const {
        if (row <= row_num || row_num < 0 || col <= col_num || col_num < 0){
            throw(out_of_range("Error : row = " + to_string(row_num) + ", col = " + to_string(col_num)));
        } else {
            return m[row_num][col_num];
        }
    }

    int& At(int row_num, int col_num) {
        if (row <= row_num || row_num < 0 || col <= col_num || col_num < 0){
            throw out_of_range("Error : row = " + to_string(row_num) + ", col = " + to_string(col_num));
        } else {
            return m[row_num][col_num];
        }
    }

    int GetNumRows() const {
        return row;
    }

    int GetNumColumns() const {
        return col;
    }

private:
    vector<vector<int>> m;
    int col, row;
};

istream& operator>>(istream& stream, Matrix& matrix){
    int rows, cols;
    stream >> rows >> cols;
    //cout << "R, C = " << rows << ", " << cols << endl;
    matrix.Reset(rows, cols);//Matrix(rows, cols);
    for (int i = 0; i < rows; ++i){
        for (int k = 0; k < cols; ++k){
            int elem;
            stream >> elem;
            //cout << "Read: " << elem << endl;
            matrix.At(i, k) = elem;
        }
    }
    return stream;
}

ostream& operator<<(ostream& stream, const Matrix& matrix){
    stream << matrix.GetNumRows() << " " << matrix.GetNumColumns();
    if (matrix.GetNumColumns() == 0 || matrix.GetNumRows() == 0){
        return stream;
    }
    stream << endl;
    for (int i = 0; i < matrix.GetNumRows(); ++i){
        for (int k = 0; k < matrix.GetNumColumns(); ++k){
            stream << matrix.At(i, k) << " ";
        }
        if (i < matrix.GetNumRows() - 1)
            stream << endl;
    }
    return stream;
}

Matrix operator+(const Matrix& lhs, const Matrix& rhs){
    int cols = lhs.GetNumColumns(), rows = lhs.GetNumRows();
    if ((cols == 0 || rows == 0) && (rhs.GetNumColumns() == 0 || rhs.GetNumRows() == 0))
        return Matrix();
    if (cols != rhs.GetNumColumns() || rows != rhs.GetNumRows()){
        throw(invalid_argument("Error: r1, r2 = " + to_string(lhs.GetNumRows()) + ", " + to_string(rhs.GetNumRows()) + ". c1, c2:" + to_string(lhs.GetNumColumns()) + ", " + to_string(rhs.GetNumColumns())));
    } else {
        Matrix mat(rows, cols);
        for (int i = 0; i < rows; ++i){
            for (int k = 0; k < cols; ++k){
                mat.At(i, k) = lhs.At(i, k) + rhs.At(i, k);
            }
        }
        return mat;
    }
}

bool operator==(const Matrix& lhs, const Matrix& rhs){
    int cols = lhs.GetNumColumns(), rows = lhs.GetNumRows();
    if ((cols == 0 || rows == 0) && (rhs.GetNumColumns() == 0 || rhs.GetNumRows() == 0)){

        return true;

    } else if (cols != rhs.GetNumColumns() || rows != rhs.GetNumRows()){

        return false;

    } else {

        for (int i = 0; i < rows; ++i){
            for (int k = 0; k < cols; ++k){
                if (lhs.At(i, k) != rhs.At(i, k)){
                    return false;
                }
            }
        }

    }
    return true;
}

// Реализуйте здесь
// * класс Matrix
// * оператор ввода для класса Matrix из потока istream
// * оператор вывода класса Matrix в поток ostream
// * оператор проверки на равенство двух объектов класса Matrix
// * оператор сложения двух объектов класса Matrix

int main() {
  Matrix one;
  Matrix two;

  cin >> one >> two;
  cout << (one == two) << endl;
  cin >> one;
  cout << one;
  return 0;
}
