#import "skeleton.hpp"

// I consulted the following resources for help:

int spam::test_file_exists() {
  // Test with missing file.
  // (First verify missing file doesn't exist.)
  if (spam::file_exists("SHIBBOLETH_missing.s")) {
    std::cerr << "Error: test_file_exists() failed. The failing subtest is \"Test with missing file\"." << std::endl;
    return FAIL;
  }

  // Test with non-missing file.
  // (First create a file.)
  std::ofstream input;
  input.open ("SHIBBOLETH_input.s");
  input << "# SAMPLE FILE\n";
  input.close();
  if (!spam::file_exists("SHIBBOLETH_input.s")) {
    std::cerr << "Error: test_file_exists() failed. The failing subtest is \"Test with non-missing file\"." << std::endl;
    return FAIL;
  }

  // All tests passed.
  std::cout << "Success: test_file_exists() passed." << std::endl;
  return SUCCESS;
}

int spam::test_do_stack() {
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
  std::cout << "Success: test_do_stack() passed." << std::endl;
  return SUCCESS;
}

int spam::test_do_accumulator() {
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
  std::cout << "Success: test_do_accumulator() passed." << std::endl;
  return SUCCESS;
}

int spam::test_do_help() {
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

  std::cout << "RESULTS:" << std::endl;
  std::cout << "\t" << tests_run << " tests run." << std::endl;
  std::cout << "\t" << tests_passed << " tests passed." << std::endl;
  std::cout << "\t" << tests_run - tests_passed << " tests failed." << std::endl;
  return SUCCESS;
}
