#include "test_runner.h"
#include <string>
#include <string_view>
#include <vector>
#include <list>

using namespace std;

class Translator {
public:
  Translator() {};
  void Add(string_view source, string_view target);
  string_view TranslateForward(string_view source) const;
  string_view TranslateBackward(string_view target) const;
  void Print();

private:
  list<string> strings;
  map<string_view, string_view> source_to_target, target_to_source;
  string_view emptyResult = {""};
};

void Translator::Add(string_view source, string_view target){
    auto it1 = source_to_target.find(source);
    auto it2 = target_to_source.find(target);
    if (it1 == source_to_target.end()){
        strings.push_back(string(source));
        source = string_view(strings.back());
    } else {
        source = it1 -> first;
    }
    if (it2 == target_to_source.end()){
        strings.push_back(string(target));
        target = string_view(strings.back());
    } else {
        target = it2 -> first;
    }
    source_to_target[source] = target;
    target_to_source[target] = source;

}

void Translator::Print(){
    cout << "---------" << endl;
    for (auto i: source_to_target){
        cout << i.first << ": " << i.second << endl;
    }
    cout << "---------" << endl;
    for (auto i: target_to_source){
        cout << i.first << ": " << i.second << endl;
    }
    cout << "---------" << endl;
}

string_view Translator::TranslateForward(string_view source) const {
    if (source_to_target.count(source) == 0) {
        //cout << source << " doesn't contains" << endl;
        return emptyResult;
    } else {
        return source_to_target.at(source);
    }
}

string_view Translator::TranslateBackward(string_view target) const {
    if (target_to_source.count(target) == 0) {
        //cout << target << " doesn't contains" << endl;
        return emptyResult;
    } else {
        return target_to_source.at(target);
    }
}

void TestSimple() {
  Translator translator;
  translator.Add(string("okno"), string("window"));
  translator.Add(string("okno"), string("window12"));
  translator.Add(string("okno"), string("window13"));
  translator.Add(string("stol"), string("table"));
  translator.Add(string("stol1"), string("table"));
  //translator.Print();

  ASSERT_EQUAL(translator.TranslateForward("okno"), "window13");
  ASSERT_EQUAL(translator.TranslateBackward("table"), "stol1");
  ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSimple);
  return 0;
}
