#include "test.hpp"

#define X 3
#define Y 7
#define Z 6

int main(int argc, char ** argv){

  bool isVerbose = false;

  if(argc > 1 && strcmp(argv[1], "-v") == 0) isVerbose = true;

  int tests_run = 1;
  int tests_passed = tests_run;
  int tests_failed;

  tests_passed += spam::test_push();

  tests_failed = tests_run - tests_passed;

  if (tests_run > 0) {
    std::cout << "RESULTS:" << std::endl;
    std::cout << "\t" << tests_run << " " << ((tests_run != 1) ? "tests" : "test") << " run." << std::endl;
  }

  if (tests_passed > 0) {
    std::cout << "\t" << COLOR_GREEN << tests_passed << " " << ((tests_run != 1) ? "tests" : "test") << " passed." << COLOR_STOP << std::endl;
  } else {
    std::cout << "\t" << tests_passed << " tests passed." << std::endl;
  }

  if (tests_failed > 0) {
    std::cout << "\t" << COLOR_RED << tests_failed << " " << ((tests_run != 1) ? "tests" : "test") << " failed." << COLOR_STOP << std::endl;
  } else {
    std::cout << "\t" << tests_failed << " tests failed." << std::endl;
  }

  return (tests_failed == 0) ? SUCCESS: FAIL;
}

int spam::test_push() {

  Stack s;

  char* memline;
  // memline = s.m.read(X_ADDR);

  if(!s.push(X_ADDR)) {
    std::cout << COLOR_RED << "Error: " << COLOR_STOP;
    std::cout << "push() returned false, true was expected." << std::endl;
    return -1;
  }

  if(strcmp(memline, s.m.read(S_BASE_ADDR)) != 0) {
    std::cout << COLOR_RED << "Error: " << COLOR_STOP;
    std::cout << "push() failed to load " << memline << "onto the stack." << std::endl;
    return -1;
  }

  if(s.sp != 0) {
    std::cout << COLOR_RED << "Error: " << COLOR_STOP;
    std::cout << "push() failed to increment stack pointer." << std::endl;
    return -1;
  }

  return 0;
}
