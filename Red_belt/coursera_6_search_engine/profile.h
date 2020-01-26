
#pragma once

#include <chrono>
#include <iostream>
#include <string>

using namespace std;
using namespace std::chrono;

class LogDuration {
public:
  explicit LogDuration(const string& msg = "")
    : message(msg + ": ")
    , start(steady_clock::now())
  {
  }

  ~LogDuration() {
    auto finish = steady_clock::now();
    auto dur = finish - start;
    cerr << message
       << duration_cast<milliseconds>(dur).count()
       << " ms" << endl;
    for (auto& i: duration) {
        cerr << i.first << " :"
             << duration_cast<milliseconds>(i.second).count()
             << " ms" << endl;
    }
  }

  void start_timer(const string& name) {
    start_times[name] = steady_clock::now();
  }

  void finish_timer(const string& name) {
    duration[name] += steady_clock::now() - start_times[name];
  }

private:
  string message;
  steady_clock::time_point start;
  map<string, steady_clock::duration> duration;
  map<string, steady_clock::time_point> start_times;
};

#define UNIQ_ID_IMPL(lineno) _a_local_var_##lineno
#define UNIQ_ID(lineno) UNIQ_ID_IMPL(lineno)

#define LOG_DURATION(message) \
  LogDuration UNIQ_ID(__LINE__){message};
