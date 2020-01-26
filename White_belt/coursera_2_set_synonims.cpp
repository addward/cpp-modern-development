#include <iostream>
#include <set>
#include <map>

using namespace std;

int main(){
    int num;
    cin >> num;
    map<string, set<string>> synonims;
    for (int i = 0; i < num; ++i){
        string command;
        cin >> command;
        if (command == "ADD"){
            string word1, word2;
            cin >> word1 >> word2;
            synonims[word1].insert(word2);
            synonims[word2].insert(word1);
        } else if (command == "COUNT"){
            string word;
            cin >> word;
            if (synonims.count(word) == 0)
                cout << "0" << endl;
            else
                cout << synonims[word].size() << endl;
        } else if (command == "CHECK"){
            string word1, word2;
            cin >> word1 >> word2;
            if (synonims.count(word1) == 1 && synonims[word1].count(word2) == 1)
                cout << "YES" << endl;
            else
                cout << "NO" << endl;
        }
    }

    return 0;
}
