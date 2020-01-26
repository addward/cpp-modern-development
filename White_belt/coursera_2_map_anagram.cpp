#include <iostream>
#include <map>
#include <vector>

using namespace std;

map<char, int> BuildCharCounters(string& w){
    map<char, int> charMap;
    for(auto c: w){
        charMap[c] += 1;
    }
    return charMap;
}

int main(){
int num;
cin >> num;
vector<string> words;
vector<string> results(num, "NO");

for (int i = 0; i < num * 2; i++){
    string word;
    cin >> word;
    words.push_back(word);
}

for (int i = 0; i < num; i++){
    map<char, int> first = BuildCharCounters(words[2*i+1]);
    map<char, int> second = BuildCharCounters(words[2*i]);
    if (first == second) results[i] = "YES";
}

for (auto i: results){
    cout << i << endl;
}

return 0;
}
