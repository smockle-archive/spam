#import "test_skeleton.hpp"

// I consulted the following resources for help:
// http://stackoverflow.com/questions/10337248/what-does-the-g-d-flag-do

int spam::test_file_exists() {
  // Test with missing file.
  // (First verify missing file doesn't exist.)
  if (spam::file_exists("SHIBBOLETH_missing.s")) {
    std::cerr << COLOR_ERROR << " test_file_exists() failed. The failing subtest is \"Test with missing file\"." << std::endl;
    return FAIL;
  }

  // Test with non-missing file.
  // (First create a file.)
  std::ofstream input;
  input.open ("SHIBBOLETH_input.s");
  input << "# SAMPLE FILE\n";
  input.close();
  if (!spam::file_exists("SHIBBOLETH_input.s")) {
    std::cerr << COLOR_ERROR << " test_file_exists() failed. The failing subtest is \"Test with non-missing file\"." << std::endl;
    return FAIL;
  }

  // All tests passed.
  std::cout << COLOR_SUCCESS << " test_file_exists() passed." << std::endl;
  return SUCCESS;
}

int spam::test_do_stack() {
  std::cerr << COLOR_ERROR << " test_do_stack() failed. The tests haven't been written yet." << std::endl;
  return FAIL;

  // Test zero arguments.
  //

  // Test one argument.
  // spam

  // Test two arguments.
  // spam stack

  // Test three arguments.
  // spam stack "SHIBBOLETH_input.s"

  // Test incorrect first argument.
  // spam missing ""

  // Test correct first argument.
  // spam stack ""

  // Test with missing file.
  // spam stack "SHIBBOLETH_missing.s"

  // Test with non-missing file.
  // spam stack "SHIBBOLETH_input.s"

  // All tests passed.
  std::cout << COLOR_SUCCESS << " test_do_stack() passed." << std::endl;
  return SUCCESS;
}

int spam::test_do_accumulator() {
  std::cerr << COLOR_ERROR << " test_do_accumulator() failed. The tests haven't been written yet." << std::endl;
  return FAIL;

  // Test zero arguments.
  //

  // Test one argument.
  // spam

  // Test two arguments.
  // spam stack

  // Test three arguments.
  // spam stack "SHIBBOLETH_input.s"

  // Test incorrect first argument.
  // spam missing ""

  // Test correct first argument.
  // spam stack ""

  // Test with missing file.
  // spam stack "SHIBBOLETH_missing.s"

  // Test with non-missing file.
  // spam stack "SHIBBOLETH_input.s"

  // All tests passed.
  std::cout << COLOR_SUCCESS << " test_do_accumulator() passed." << std::endl;
  return SUCCESS;
}

int spam::test_do_help() {
  std::cerr << COLOR_ERROR << " test_do_help() failed. The tests haven't been written yet." << std::endl;
  return FAIL;

  // Verify returns true.

  // All tests passed.
  std::cout << "Success: test_do_help() passed." << std::endl;
  return SUCCESS;
}

int main(int argc, char** argv) {
  int tests_run = 4;
  int tests_passed = 0;

  tests_passed += spam::test_file_exists();
  tests_passed += spam::test_do_stack();
  tests_passed += spam::test_do_accumulator();
  tests_passed += spam::test_do_help();

  int tests_failed = tests_run - tests_passed;

  if (tests_run > 0) {
    std::cout << "RESULTS:" << std::endl;
    if (tests_run > 1) {
      std::cout << "\t" << tests_run << " tests run." << std::endl;
    } else {
      std::cout << "\t" << tests_run << " test run." << std::endl;
    }
  }

  if (tests_passed > 1) {
    std::cout << "\t" << COLOR_GREEN << tests_passed << " tests passed." << COLOR_STOP << std::endl;
  } else if (tests_passed == 1) {
    std::cout << "\t" << COLOR_GREEN << tests_passed << " test passed." << COLOR_STOP << std::endl;
  } else {
    std::cout << "\t" << tests_passed << " tests passed." << std::endl;
  }

  if (tests_failed > 1) {
    std::cout << "\t" << COLOR_RED << tests_failed << " tests failed." << COLOR_STOP << std::endl;
  } else if (tests_failed == 1) {
    std::cout << "\t" << COLOR_RED << tests_failed << " test failed." << COLOR_STOP << std::endl;
  } else {
    std::cout << "\t" << tests_failed << " tests failed." << std::endl;
  }

  return SUCCESS;
}
