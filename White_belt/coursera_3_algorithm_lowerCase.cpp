#include <vector>
#include <algorithm>
#include <iostream>
#include <locale>

using namespace std;

int main(){
    int n;
    cin >> n;
    vector <string> words(n);

    for(int i = 0; i < n; ++i){
        string word;
        cin >> word;
        words[i] = word;
    }
    sort(begin(words), end(words), [](string w1, string w2){
         for (int i = 0; i < w1.size(); i++){
            w2[i] = tolower(w2[i]);
        }
        for (int i = 0; i < w2.size(); i++){
            w1[i] = tolower(w1[i]);
        }
         return w1 < w2;});

    for (auto &i: words){
        cout << i << " ";
    }
    cout << endl;

    return 0;
}
