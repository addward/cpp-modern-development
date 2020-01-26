#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

int main(){
    ifstream is("input.txt");
    ofstream os("output.txt");
    string buf;

    while (getline(is, buf)){
        os << buf << endl;
    }


    return 0;
}
