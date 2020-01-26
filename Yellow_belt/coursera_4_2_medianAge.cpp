#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
/*
enum class Gender {
  FEMALE,
  MALE
};

struct Person {
  int age;  // возраст
  Gender gender;  // пол
  bool is_employed;  // имеет ли работу
};

template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
  if (range_begin == range_end) {
    return 0;
  }
  vector<typename InputIt::value_type> range_copy(range_begin, range_end);
  auto middle = begin(range_copy) + range_copy.size() / 2;
  nth_element(
      begin(range_copy), middle, end(range_copy),
      [](const Person& lhs, const Person& rhs) {
        return lhs.age < rhs.age;
      }
  );
  return middle->age;
}
*/
void PrintStats(vector<Person> persons){
    cout << "Median age = " << ComputeMedianAge(begin(persons), end(persons)) << endl;

    // Gender divider
    auto femaleEnd = partition(begin(persons), end(persons), [](Person& p){
                return (p.gender == Gender::FEMALE);
              });
    cout << "Median age for females = " << ComputeMedianAge(begin(persons), femaleEnd) << endl;
    cout << "Median age for males = " << ComputeMedianAge(femaleEnd, end(persons)) << endl;

    // Employed Female divider
    auto employedFemaleEnd = partition(begin(persons), femaleEnd, [](Person& p){
                return (p.is_employed == true);
              });
    cout << "Median age for employed females = " << ComputeMedianAge(begin(persons), employedFemaleEnd) << endl;
    cout << "Median age for unemployed females = " << ComputeMedianAge(employedFemaleEnd, femaleEnd) << endl;

    // Employed Male divider
    auto employedMaleEnd = partition(femaleEnd, end(persons), [](Person& p){
                return (p.is_employed == true);
              });
    cout << "Median age for employed males = " << ComputeMedianAge(femaleEnd, employedMaleEnd) << endl;
    cout << "Median age for unemployed males = " << ComputeMedianAge(employedMaleEnd, end(persons)) << endl;

}

int main() {
  vector<Person> persons = {
      {31, Gender::MALE, false},
      {40, Gender::FEMALE, true},
      {24, Gender::MALE, true},
      {20, Gender::FEMALE, true},
      {80, Gender::FEMALE, false},
      {78, Gender::MALE, false},
      {10, Gender::FEMALE, false},
      {55, Gender::MALE, true},
  };
  PrintStats(persons);
  return 0;
}
