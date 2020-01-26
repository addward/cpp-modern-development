#include <iostream>
#include <vector>
#include <map>
#include <utility>

using namespace std;

template <typename Num> Num Sqr(Num n);
template <typename T> vector<T> Sqr(const vector<T>& v);
template <typename K, typename V> map<K, V> Sqr(const map<K, V>& m);
template <typename T1, typename T2> pair<T1, T2> Sqr(const pair<T1, T2>& p);

template <typename Num>
Num Sqr(Num n){
    return (n * n);
}

template <typename T>
vector<T> Sqr(const vector<T>& v){
    vector<T> sqr_v;
    for (const auto& el: v){
        sqr_v.push_back(Sqr(el));
    }
    return sqr_v;
}

template <typename K, typename V>
map<K, V> Sqr(const map<K, V>& m){
    map<K, V> sqr_m;
    for(const auto& el: m){
        sqr_m[el.first] = Sqr(el.second);
    }
    return sqr_m;
}

template <typename T1, typename T2>
pair<T1, T2> Sqr(const pair<T1, T2>& p){
    return {Sqr(p.first), Sqr(p.second)};
}

int main(){
        vector<int> v = {1, 2, 3};
cout << "vector:";
for (int x : Sqr(v)) {
  cout << ' ' << x;
}
cout << endl;

map<int, pair<int, int>> map_of_pairs = {
  {4, {2, 2}},
  {7, {4, 3}}
};
cout << "map of pairs:" << endl;
for (const auto& x : Sqr(map_of_pairs)) {
  cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
}
}
