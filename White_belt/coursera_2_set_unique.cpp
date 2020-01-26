#include <set>
#include <iostream>

using namespace std;

int main(){
    int num;
    cin >> num;
    set<string> words;

    for (int i = 0; i < num; i++){
        string word;
        cin >> word;
        words.insert(word);
    }
    cout << words.size();
    return 0;
}
