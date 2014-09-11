#include "test_skeleton.hpp"

// I consulted the following resources for help:
// http://stackoverflow.com/questions/10337248/what-does-the-g-d-flag-do
// http://stackoverflow.com/questions/347949/convert-stdstring-to-const-char-or-char

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
  // Test zero arguments.
  //
  char* argv[0];
  if (spam::do_stack(0, argv) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << " test_do_stack() failed. The failing subtest is \"Test zero arguments\"." << std::endl;
    return FAIL;
  }

  // Test one argument.
  // spam
  char* argh[] = { (char*) "spam" };
  if (spam::do_stack(1, argh) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << " test_do_stack() failed. The failing subtest is \"Test one argument\"." << std::endl;
    return FAIL;
  }

  // Test two arguments.
  // spam stack
  char* argi[] = { (char*) "spam", (char*) "stack" };
  if (spam::do_stack(2, argi) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << " test_do_stack() failed. The failing subtest is \"Test two arguments\"." << std::endl;
    return FAIL;
  }

  // Test three arguments.
  // spam stack "SHIBBOLETH_input.s"
  char* argj[] = { (char*) "spam", (char*) "stack", (char*) "SHIBBOLETH_input.s" };
  if (spam::do_stack(3, argj) == ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << " test_do_stack() failed. The failing subtest is \"Test three arguments\"." << std::endl;
    return FAIL;
  }

  // Test incorrect first argument.
  // spam missing ""
  char* argk[] = { (char*) "spam", (char*) "missing", (char*) "" };
  if (spam::do_stack(3, argk) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << " test_do_stack() failed. The failing subtest is \"Test incorrect first argument\"." << std::endl;
    return FAIL;
  }

  // Test correct first argument.
  // spam stack ""
  char* argl[] = { (char*) "spam", (char*) "stack", (char*) "" };
  if (spam::do_stack(3, argl) == ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << " test_do_stack() failed. The failing subtest is \"Test correct first argument\"." << std::endl;
    return FAIL;
  }

  // Test with missing file.
  // spam stack "SHIBBOLETH_missing.s"
  char* argm[] = { (char*) "spam", (char*) "stack", (char*) "SHIBBOLETH_missing.s" };
  if (spam::do_stack(3, argm) != IO_ERROR) {
    std::cerr << COLOR_ERROR << " test_do_stack() failed. The failing subtest is \"Test with missing file\"." << std::endl;
    return FAIL;
  }

  // Test with non-missing file.
  // spam stack "SHIBBOLETH_input.s"
  // (First create a file.)
  std::ofstream input;
  input.open ("SHIBBOLETH_input.s");
  input << "# SAMPLE FILE\n";
  input.close();
  char* argn[] = { (char*) "spam", (char*) "stack", (char*) "SHIBBOLETH_input.s" };
  if (spam::do_stack(3, argn) == IO_ERROR) {
    std::cerr << COLOR_ERROR << " test_do_stack() failed. The failing subtest is \"Test with non-missing file\"." << std::endl;
    return FAIL;
  }

  // All tests passed.
  std::cout << COLOR_SUCCESS << " test_do_stack() passed." << std::endl;
  return SUCCESS;
}

int spam::test_do_accumulator() {
  // Test zero arguments.
  //
  char* argv[0];
  if (spam::do_accumulator(0, argv) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << " test_do_accumulator() failed. The failing subtest is \"Test zero arguments\"." << std::endl;
    return FAIL;
  }

  // Test one argument.
  // spam
  char* argh[] = { (char*) "spam" };
  if (spam::do_accumulator(1, argh) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << " test_do_accumulator() failed. The failing subtest is \"Test one argument\"." << std::endl;
    return FAIL;
  }

  // Test two arguments.
  // spam stack
  char* argi[] = { (char*) "spam", (char*) "accumulator" };
  if (spam::do_accumulator(2, argi) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << " test_do_accumulator() failed. The failing subtest is \"Test two arguments\"." << std::endl;
    return FAIL;
  }

  // Test three arguments.
  // spam stack "SHIBBOLETH_input.s"
  char* argj[] = { (char*) "spam", (char*) "accumulator", (char*) "SHIBBOLETH_input.s" };
  if (spam::do_accumulator(3, argj) == ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << " test_do_accumulator() failed. The failing subtest is \"Test three arguments\"." << std::endl;
    return FAIL;
  }

  // Test incorrect first argument.
  // spam missing ""
  char* argk[] = { (char*) "spam", (char*) "missing", (char*) "" };
  if (spam::do_accumulator(3, argk) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << " test_do_accumulator() failed. The failing subtest is \"Test incorrect first argument\"." << std::endl;
    return FAIL;
  }

  // Test correct first argument.
  // spam stack ""
  char* argl[] = { (char*) "spam", (char*) "accumulator", (char*) "" };
  if (spam::do_accumulator(3, argl) == ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << " test_do_accumulator() failed. The failing subtest is \"Test correct first argument\"." << std::endl;
    return FAIL;
  }

  // Test with missing file.
  // spam stack "SHIBBOLETH_missing.s"
  char* argm[] = { (char*) "spam", (char*) "accumulator", (char*) "SHIBBOLETH_missing.s" };
  if (spam::do_accumulator(3, argm) != IO_ERROR) {
    std::cerr << COLOR_ERROR << " test_do_accumulator() failed. The failing subtest is \"Test with missing file\"." << std::endl;
    return FAIL;
  }

  // Test with non-missing file.
  // spam stack "SHIBBOLETH_input.s"
  // (First create a file.)
  std::ofstream input;
  input.open ("SHIBBOLETH_input.s");
  input << "# SAMPLE FILE\n";
  input.close();
  char* argn[] = { (char*) "spam", (char*) "accumulator", (char*) "SHIBBOLETH_input.s" };
  if (spam::do_accumulator(3, argn) == IO_ERROR) {
    std::cerr << COLOR_ERROR << " test_do_accumulator() failed. The failing subtest is \"Test with non-missing file\"." << std::endl;
    return FAIL;
  }

  // All tests passed.
  std::cout << COLOR_SUCCESS << " test_do_accumulator() passed." << std::endl;
  return SUCCESS;
}

int spam::test_do_help() {
  // Verify returns true.
  if (spam::do_help() != SUCCESS) {
    std::cerr << COLOR_ERROR << " test_do_help() failed. The failing subtest is \"Verify returns true\"." << std::endl;
    return FAIL;
  }

  // All tests passed.
  std::cout << COLOR_SUCCESS << " test_do_help() passed." << std::endl;
  return SUCCESS;
}

std::string spam::pluralize_test(int i) {
  return (i != 1) ? "tests" : "test";
}

int spam::test_pluralize_test() {
  // Test a negative number.
  if (std::strcmp(spam::pluralize_test(-4).c_str(), "tests") != 0) {
    std::cerr << COLOR_ERROR << " test_pluralize_test() failed. The failing subtest is \"Test a negative number\"." << std::endl;
    return FAIL;
  }

  // Test zero.
  if (std::strcmp(spam::pluralize_test(0).c_str(), "tests") != 0) {
    std::cerr << COLOR_ERROR << " test_pluralize_test() failed. The failing subtest is \"Test zero\"." << std::endl;
    return FAIL;
  }

  // Test one.
  if (std::strcmp(spam::pluralize_test(1).c_str(), "test") != 0) {
    std::cerr << COLOR_ERROR << " test_pluralize_test() failed. The failing subtest is \"Test one\"." << std::endl;
    return FAIL;
  }

  // Test a positive number.
  if (std::strcmp(spam::pluralize_test(4).c_str(), "tests") != 0) {
    std::cerr << COLOR_ERROR << " test_pluralize_test() failed. The failing subtest is \"Test a positive number\"." << std::endl;
    return FAIL;
  }

  // All tests passed.
  std::cout << COLOR_SUCCESS << " test_pluralize_test() passed." << std::endl;
  return SUCCESS;
}

int main(int argc, char** argv) {
  int tests_run = 5;
  int tests_passed = 5;

  tests_passed += spam::test_file_exists();
  tests_passed += spam::test_do_stack();
  tests_passed += spam::test_do_accumulator();
  tests_passed += spam::test_do_help();
  tests_passed += spam::test_pluralize_test();

  int tests_failed = tests_run - tests_passed;

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
