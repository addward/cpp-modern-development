#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

int main(){
    ifstream file("input.txt");
    int columns, rows;
    file >> rows >> columns;
    int number;
    for (int i = 0; i < rows; ++i){
        for (int k = 0; k < columns; ++k){
            file >> number;
            file.ignore(1);
            cout << setw(10) << number;
            if (k != columns - 1)
                cout << " ";
        }
        if (i != rows - 1)
            cout << endl;
    }
}
