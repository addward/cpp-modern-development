#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <set>

using namespace std;

class Learner {
 private:
  set<string> _unique_dict;
  vector<string> dict;

 public:
  int Learn(const vector<string>& words) {
    int newWords = 0;
    for (const auto& word : words) {
      if (_unique_dict.insert(word).second == true){
        ++newWords;
      }
      /*if (find(dict.begin(), dict.end(), word) == dict.end()) {
        ++newWords;
        dict.push_back(word);
      }*/
    }
    return newWords;
  }

  vector<string> KnownWords() {
    //sort(dict.begin(), dict.end());
    //dict.erase(unique(dict.begin(), dict.end()), dict.end());
    //return dict;
    return {begin(_unique_dict), end(_unique_dict)};
  }
};

int main() {
  Learner learner;
  string line;
  while (getline(cin, line)) {
    vector<string> words;
    stringstream ss(line);
    string word;
    while (ss >> word) {
      words.push_back(word);
    }
    cout << learner.Learn(words) << "\n";
  }
  cout << "=== known words ===\n";
  for (auto word : learner.KnownWords()) {
    cout << word << "\n";
  }
}
