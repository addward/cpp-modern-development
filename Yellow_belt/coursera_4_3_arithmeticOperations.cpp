#include <iostream>
#include <string>
#include <deque>

using namespace std;

int main(){
    uint32_t size;
    int32_t number;
    cin >> number >> size;
    deque<string> expression;
    expression.push_back(to_string(number));
    for (uint32_t i = 0; i < size; i++){
        char operation;
        int  num;

        cin >> operation;
        cin >> num;
    /*
        if (num < 0){
            if (operation == '+'){
                operation = '-';
                num *= -1;
            } else if (operation == '-'){
                operation = '+';
                num *= -1;
            }
        }
*/
        expression.push_back( ") " + string(1, operation) + " " + to_string(num));
        expression.push_front("(");
    }
    for (auto it = expression.begin(); it != expression.end(); ++it){
        cout << *it;
    }
    cout << endl;
}
