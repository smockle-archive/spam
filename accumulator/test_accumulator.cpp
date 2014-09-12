#include "test_accumulator.hpp"

spam::TestAccumulator::TestAccumulator() {
}

int spam::TestAccumulator::test_accumulator_load() {
  // Test negative address.
  if (accumulator.load(-4) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << " test_accumulator_load() failed. The failing subtest is \"Test negative address\"." << std::endl;
    return FAIL;
  }

  // Test positive address.accumulator.a = 0;
  accumulator.memory.store(TEST_ADDRESS, (char *) "SHIBBOLETH");
  if (accumulator.load(TEST_ADDRESS) == ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << " test_accumulator_load() failed. The failing subtest is \"Test postive address\"." << std::endl;
    return FAIL;
  }

  // Test value that can't be converted to integer.
  accumulator.memory.store(TEST_ADDRESS, (char *) "SHIBBOLETH");
  if (accumulator.load(TEST_ADDRESS) != TYPE_ERROR) {
    std::cerr << COLOR_ERROR << " test_accumulator_load() failed. The failing subtest is \"Test value that can't be converted to integer\"." << std::endl;
    return FAIL;
  }

  // Test value that can be converted to integer.
  accumulator.memory.store(TEST_ADDRESS, (char *) "1");
  if (accumulator.load(TEST_ADDRESS) == TYPE_ERROR) {
    std::cerr << COLOR_ERROR << " test_accumulator_load() failed. The failing subtest is \"Test value that can be converted to integer\"." << std::endl;
    return FAIL;
  }

  // All tests passed.
  std::cout << COLOR_SUCCESS << " test_accumulator_load() passed." << std::endl;
  return SUCCESS;
}

int spam::TestAccumulator::test_accumulator_store() {
  // Test negative address.
  if (accumulator.store(-4) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << " test_accumulator_store() failed. The failing subtest is \"Test negative address\"." << std::endl;
    return FAIL;
  }

  // Test positive address.
  if (accumulator.store(TEST_ADDRESS) == ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << " test_accumulator_store() failed. The failing subtest is \"Test postive address\"." << std::endl;
    return FAIL;
  }

  // All tests passed.
  std::cout << COLOR_SUCCESS << " test_accumulator_store() passed." << std::endl;
  return SUCCESS;
}

int spam::TestAccumulator::test_accumulator_add() {
  // Test negative address.
  if (accumulator.add(-4) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << " test_accumulator_add() failed. The failing subtest is \"Test negative address\"." << std::endl;
    return FAIL;
  }

  // Test positive address.
  if (accumulator.add(TEST_ADDRESS) == ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << " test_accumulator_add() failed. The failing subtest is \"Test postive address\"." << std::endl;
    return FAIL;
  }

  // Test value that can't be converted to integer.
  accumulator.memory.store(TEST_ADDRESS, (char *) "SHIBBOLETH");
  if (accumulator.add(TEST_ADDRESS) != TYPE_ERROR) {
    std::cerr << COLOR_ERROR << " test_accumulator_add() failed. The failing subtest is \"Test value that can't be converted to integer\"." << std::endl;
    return FAIL;
  }

  // Test value that can be converted to integer.
  accumulator.memory.store(TEST_ADDRESS, (char *) "1");
  if (accumulator.add(TEST_ADDRESS) == TYPE_ERROR) {
    std::cerr << COLOR_ERROR << " test_accumulator_add() failed. The failing subtest is \"Test value that can be converted to integer\"." << std::endl;
    return FAIL;
  }

  // Verify sum correctness.
  accumulator.a = 0;
  accumulator.memory.store(TEST_ADDRESS, (char *) "1");
  accumulator.add(TEST_ADDRESS);
  if (accumulator.a != 1) {
    std::cerr << COLOR_ERROR << " test_accumulator_add() failed. The failing subtest is \"Verify sum correctness\"." << std::endl;
    return FAIL;
  }

  // All tests passed.
  std::cout << COLOR_SUCCESS << " test_accumulator_add() passed." << std::endl;
  return SUCCESS;
}

int spam::TestAccumulator::test_accumulator_multiply() {
  // Test negative address.
  if (accumulator.multiply(-4) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << " test_accumulator_multiply() failed. The failing subtest is \"Test negative address\"." << std::endl;
    return FAIL;
  }

  // Test positive address.
  if (accumulator.multiply(TEST_ADDRESS) == ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << " test_accumulator_multiply() failed. The failing subtest is \"Test postive address\"." << std::endl;
    return FAIL;
  }

  // Test value that can't be converted to integer.
  accumulator.memory.store(TEST_ADDRESS, (char *) "SHIBBOLETH");
  if (accumulator.multiply(TEST_ADDRESS) != TYPE_ERROR) {
    std::cerr << COLOR_ERROR << " test_accumulator_multiply() failed. The failing subtest is \"Test value that can't be converted to integer\"." << std::endl;
    return FAIL;
  }

  // Test value that can be converted to integer.
  accumulator.memory.store(TEST_ADDRESS, (char *) "3");
  if (accumulator.multiply(TEST_ADDRESS) == TYPE_ERROR) {
    std::cerr << COLOR_ERROR << " test_accumulator_multiply() failed. The failing subtest is \"Test value that can be converted to integer\"." << std::endl;
    return FAIL;
  }

  // Verify product correctness.
  accumulator.a = 2;
  accumulator.memory.store(TEST_ADDRESS, (char *) "3");
  accumulator.multiply(TEST_ADDRESS);
  if (accumulator.a != 6) {
    std::cerr << COLOR_ERROR << " test_accumulator_multiply() failed. The failing subtest is \"Verify product correctness\"." << std::endl;
    return FAIL;
  }

  // All tests passed.
  std::cout << COLOR_SUCCESS << " test_accumulator_multiply() passed." << std::endl;
  return SUCCESS;
}

int spam::TestAccumulator::test_accumulator_end() {
  // Verify returns true.
  if (accumulator.end() != SUCCESS) {
    std::cerr << COLOR_ERROR << " test_accumulator_end() failed. The failing subtest is \"Verify returns true\"." << std::endl;
    return FAIL;
  }

  // All tests passed.
  std::cout << COLOR_SUCCESS << " test_accumulator_end() passed." << std::endl;
  return SUCCESS;
}

int main(int argc, char** argv) {
  spam::TestAccumulator testaccumulator;

  int tests_run = 5;
  int tests_passed = 5;

  tests_passed += testaccumulator.test_accumulator_load();
  tests_passed += testaccumulator.test_accumulator_store();
  tests_passed += testaccumulator.test_accumulator_add();
  tests_passed += testaccumulator.test_accumulator_multiply();
  tests_passed += testaccumulator.test_accumulator_end();

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
