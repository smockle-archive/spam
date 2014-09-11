#include "stack.hpp"
#include "../utilities.hpp"

#include "test.hpp"

#define X 3
#define Y 7
#define Z 6

int main(int argc, char ** argv){

  bool isVerbose = false;

  if(argc > 1 && strcmp(argv[1], "-v") == 0) isVerbose = true;

  int tests_run = 1;
  int tests_passed = 1;
  int tests_failed;

  tests_passed += spam::test_push();

  tests_failed = tests_run - tests_passed;

  if (tests_run > 0) {
    std::cout << "RESULTS:" << std::endl;
    std::cout << "\t" << tests_run << " " << spam::pluralize_test(tests_run) << " run." << std::endl;
  }

  if (tests_passed > 0) {
    std::cout << "\t" << COLOR_GREEN << tests_passed << " " << spam::pluralize_test(tests_passed) << " passed." << COLOR_STOP << std::endl;
  } else {
    std::cout << "\t" << tests_passed << " tests passed." << std::endl;
  }

  if (tests_failed > 0) {
    std::cout << "\t" << COLOR_RED << tests_failed << " " << spam::pluralize_test(tests_failed) << " failed." << COLOR_STOP << std::endl;
  } else {
    std::cout << "\t" << tests_failed << " tests failed." << std::endl;
  }

  return (tests_failed == 0) ? SUCCESS: FAIL;
}

int spam::test_push() {

  StackSim s;

  char* memline;
  memline = s.m.read(X_ADDR);

  return -1;
}
