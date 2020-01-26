#include "test_runner.h"

#include <ostream>
#include <iostream>
using namespace std;

#define PRINT_VALUES(out, x, y) if (1 > 0){ \
    out << (x) << std::endl;      \
    out << (y) << std::endl;      \
} else

int main() {
  TestRunner tr;
  tr.RunTest([] {
    ostringstream output;
    PRINT_VALUES(output, 4, "red belt");
    ASSERT_EQUAL(output.str(), "4\nred belt\n");
  }, "PRINT_VALUES usage example");
  tr.RunTest([] {
             ostringstream output;
             PRINT_VALUES(output,"abc", "dcf");
             ASSERT_EQUAL(output.str(), "abc\ndcf\n");
             }, "PRINT_VALUES const string");
}
