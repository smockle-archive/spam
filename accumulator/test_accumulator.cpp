#include "test_accumulator.hpp"

int spam::test_accumulator_load() {
  std::cerr << COLOR_ERROR << " test_accumulator_end() failed. Tests have not been written yet." << std::endl;
  return FAIL;
}

int spam::test_accumulator_store() {
  std::cerr << COLOR_ERROR << " test_accumulator_end() failed. Tests have not been written yet." << std::endl;
  return FAIL;
}

int spam::test_accumulator_add() {
  std::cerr << COLOR_ERROR << " test_accumulator_end() failed. Tests have not been written yet." << std::endl;
  return FAIL;
}

int spam::test_accumulator_multiply() {
  std::cerr << COLOR_ERROR << " test_accumulator_end() failed. Tests have not been written yet." << std::endl;
  return FAIL;
}

int spam::test_accumulator_end() {
  std::cerr << COLOR_ERROR << " test_accumulator_end() failed. Tests have not been written yet." << std::endl;
  return FAIL;
}

int main(int argc, char** argv) {
  int tests_run = 5;
  int tests_passed = 5;

  tests_passed += spam::test_accumulator_load();
  tests_passed += spam::test_accumulator_store();
  tests_passed += spam::test_accumulator_add();
  tests_passed += spam::test_accumulator_multiply();
  tests_passed += spam::test_accumulator_end();

  int tests_failed = tests_run - tests_passed;

  if (tests_run > 0) {
    std::cout << "RESULTS:" << std::endl;
    std::cout << "\t" << tests_run << " " << (tests_run != 1 ? "tests" : "test")  << " run." << std::endl;
  }

  if (tests_passed > 0) {
    std::cout << "\t" << COLOR_GREEN << tests_passed << " " << (tests_passed != 1 ? "tests" : "test") << " passed." << COLOR_STOP << std::endl;
  } else {
    std::cout << "\t" << tests_passed << " tests passed." << std::endl;
  }

  if (tests_failed > 0) {
    std::cout << "\t" << COLOR_RED << tests_failed << " " << (tests_failed != 1 ? "tests" : "test") << " failed." << COLOR_STOP << std::endl;
  } else {
    std::cout << "\t" << tests_failed << " tests failed." << std::endl;
  }

  return (tests_failed == 0) ? SUCCESS: FAIL;
}
