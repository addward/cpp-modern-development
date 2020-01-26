#include <iostream>
#include <string>
#include <deque>
#include <sstream>

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
        if (expression.end() - expression.begin() > 2){
            if ((*(expression.end() - 2) == "+" || *(expression.end() - 2) == "-") &&
                (operation == '*' || operation == '/')){
                    expression.push_back(") ");
                    expression.push_front("(");
                }
            else {
                expression.push_back(" ");
            }
        } else {
            expression.push_back(" ");
        }

        expression.push_back(string(1,operation));
        expression.push_back(" " + to_string(num));
    }
    stringstream str;
    string result;
    for (auto it = expression.begin(); it != expression.end(); ++it){
        result += *it;
    }
    cout << result;
    cout << endl;
}
