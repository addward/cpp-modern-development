#include "coursera_4_phone_number.h"
#include <iostream>

using namespace std;

int main(){
    PhoneNumber pn("+abc-def-ghi");
    cout << pn.GetInternationalNumber();
}
