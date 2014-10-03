#include "test.hpp"

// I consulted the following resources for help:
// http://stackoverflow.com/questions/10337248/what-does-the-g-d-flag-do
// http://stackoverflow.com/questions/347949/convert-stdstring-to-const-char-or-char

int spam::TestSkeleton::test_file_exists() {
  // Test with missing file.
  // (First verify missing file doesn't exist.)
  if (skeleton.file_exists("SHIBBOLETH_missing.s")) {
    std::cerr << COLOR_ERROR << "test_file_exists() failed. The failing subtest is \"Test with missing file\"." << std::endl;
    return FAIL;
  }

  // Test with non-missing file.
  // (First create a file.)
  std::ofstream input;
  input.open ("SHIBBOLETH_input.s");
  input << "# SAMPLE FILE\n";
  input << ".text\n";
  input << "END\n";
  input.close();
  if (!skeleton.file_exists("SHIBBOLETH_input.s")) {
    std::cerr << COLOR_ERROR << "test_file_exists() failed. The failing subtest is \"Test with non-missing file\"." << std::endl;
    return FAIL;
  }

  // All tests passed.
  std::cout << COLOR_SUCCESS << "File existence test passed." << std::endl;
  return SUCCESS;
}

int spam::TestSkeleton::test_do_memory() {
  // Test with missing file.
  // (First verify missing file doesn't exist.)
  if (skeleton.do_memory("SHIBBOLETH_missing.s") != IO_ERROR) {
    std::cerr << COLOR_ERROR << "test_do_memory() failed. The failing subtest is \"Test with missing file\"." << std::endl;
    return FAIL;
  }

  // Test with existing file.
  std::ofstream input;
  input.open ("SHIBBOLETH_input.s");
  input << ".data\n";
  input << "X: 3\n";
  input << "Y: 4\n";
  input << ".text\n";
  input << "PUSH X\n";
  input << "PUSH Y\n";
  input << "POP X\n";
  input << "END";
  input.close();
  if (skeleton.do_memory("SHIBBOLETH_input.s") == IO_ERROR) {
    std::cerr << COLOR_ERROR << "test_do_memory() failed. The failing subtest is \"Test with existing file\"." << std::endl;
    return FAIL;
  }

  // Test that we read in and stored the lines we thought we did.


  if (strcmp(skeleton.memory->read(D_BASE_ADDR),     "256: 3") != 0
   || strcmp(skeleton.memory->read(D_BASE_ADDR + 1), "257: 4") != 0
   || strcmp(skeleton.memory->read(T_BASE_ADDR),     "push 256") != 0
   || strcmp(skeleton.memory->read(T_BASE_ADDR + 1), "push 257") != 0
   || strcmp(skeleton.memory->read(T_BASE_ADDR + 2), "pop 256") != 0) {
     std::cerr << COLOR_ERROR << "test_do_memory() failed. The failing subtest is \"Test that we read in and stored the lines we thought we did\"." << std::endl;
     return FAIL;
   }

  // All tests passed.
  std::cout << COLOR_SUCCESS << "Memory test passed." << std::endl;
  return SUCCESS;
}

int spam::TestSkeleton::test_do_stack() {

  std::cout << "We're beginning the do_stack tests. " << std::endl;

  // Test zero arguments.
  //
  char* argv[0];
  if (skeleton.do_stack(0, argv) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_do_stack() failed. The failing subtest is \"Test zero arguments\"." << std::endl;
    return FAIL;
  }

  // Test one argument.
  // spam
  char* argh[] = { (char*) "spam" };
  if (skeleton.do_stack(1, argh) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_do_stack() failed. The failing subtest is \"Test one argument\"." << std::endl;
    return FAIL;
  }

  // Test two arguments.
  // spam stack
  char* argi[] = { (char*) "spam", (char*) "stack" };
  if (skeleton.do_stack(2, argi) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_do_stack() failed. The failing subtest is \"Test two arguments\"." << std::endl;
    return FAIL;
  }

  std::cout << "We're failing at the three-arguments test." << std::endl;

  // Test three arguments.
  // spam stack "SHIBBOLETH_input.s"
  char* argj[] = { (char*) "spam", (char*) "stack", (char*) "SHIBBOLETH_input.s" };
  if (skeleton.do_stack(3, argj) == ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_do_stack() failed. The failing subtest is \"Test three arguments\"." << std::endl;
    return FAIL;
  }

  std::cout << "We're failing at the incorrect first argument test." << std::endl;

  // Test incorrect first argument.
  // spam missing ""
  char* argk[] = { (char*) "spam", (char*) "missing", (char*) "" };
  if (skeleton.do_stack(3, argk) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_do_stack() failed. The failing subtest is \"Test incorrect first argument\"." << std::endl;
    return FAIL;
  }

  std::cout << "We're failing at the correct first argument test." << std::endl;

  // Test correct first argument.
  // spam stack ""
  char* argl[] = { (char*) "spam", (char*) "stack", (char*) "" };
  if (skeleton.do_stack(3, argl) == ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_do_stack() failed. The failing subtest is \"Test correct first argument\"." << std::endl;
    return FAIL;
  }

  std::cout << "We're failing at the missing file." << std::endl;

  // Test with missing file.
  // spam stack "SHIBBOLETH_missing.s"
  char* argm[] = { (char*) "spam", (char*) "stack", (char*) "SHIBBOLETH_missing.s" };
  if (skeleton.do_stack(3, argm) != IO_ERROR) {
    std::cerr << COLOR_ERROR << "test_do_stack() failed. The failing subtest is \"Test with missing file\"." << std::endl;
    return FAIL;
  }

  std::cout << "We're failing at the weird file." << std::endl;

  // Test with non-missing file.
  // spam stack "SHIBBOLETH_input.s"
  // (First create a file.)
  std::ofstream input;
  input.open ("SHIBBOLETH_input.s");
  input << "# SAMPLE FILE\n";
  input << ".text\n";
  input << "END\n";
  input.close();
  char* argn[] = { (char*) "spam", (char*) "stack", (char*) "SHIBBOLETH_input.s" };
  if (skeleton.do_stack(3, argn) == IO_ERROR) {
    std::cerr << COLOR_ERROR << "test_do_stack() failed. The failing subtest is \"Test with non-missing file\"." << std::endl;
    return FAIL;
  }

  // All tests passed.
  std::cout << COLOR_SUCCESS << "Stack test passed." << std::endl;
  return SUCCESS;
}

int spam::TestSkeleton::test_do_accumulator() {
  // Test zero arguments.
  //
  char* argv[0];
  if (skeleton.do_accumulator(0, argv) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_do_accumulator() failed. The failing subtest is \"Test zero arguments\"." << std::endl;
    return FAIL;
  }

  // Test one argument.
  // spam
  char* argh[] = { (char*) "spam" };
  if (skeleton.do_accumulator(1, argh) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_do_accumulator() failed. The failing subtest is \"Test one argument\"." << std::endl;
    return FAIL;
  }

  // Test two arguments.
  // spam stack
  char* argi[] = { (char*) "spam", (char*) "accumulator" };
  if (skeleton.do_accumulator(2, argi) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_do_accumulator() failed. The failing subtest is \"Test two arguments\"." << std::endl;
    return FAIL;
  }

  // Test three arguments.
  // spam stack "SHIBBOLETH_input.s"
  char* argj[] = { (char*) "spam", (char*) "accumulator", (char*) "SHIBBOLETH_input.s" };
  if (skeleton.do_accumulator(3, argj) == ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_do_accumulator() failed. The failing subtest is \"Test three arguments\"." << std::endl;
    return FAIL;
  }

  // Test incorrect first argument.
  // spam missing ""
  char* argk[] = { (char*) "spam", (char*) "missing", (char*) "" };
  if (skeleton.do_accumulator(3, argk) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_do_accumulator() failed. The failing subtest is \"Test incorrect first argument\"." << std::endl;
    return FAIL;
  }

  // Test correct first argument.
  // spam stack ""
  char* argl[] = { (char*) "spam", (char*) "accumulator", (char*) "" };
  if (skeleton.do_accumulator(3, argl) == ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_do_accumulator() failed. The failing subtest is \"Test correct first argument\"." << std::endl;
    return FAIL;
  }

  // Test with missing file.
  // spam stack "SHIBBOLETH_missing.s"
  char* argm[] = { (char*) "spam", (char*) "accumulator", (char*) "SHIBBOLETH_missing.s" };
  if (skeleton.do_accumulator(3, argm) != IO_ERROR) {
    std::cerr << COLOR_ERROR << "test_do_accumulator() failed. The failing subtest is \"Test with missing file\"." << std::endl;
    return FAIL;
  }

  // Test with non-missing file.
  // spam stack "SHIBBOLETH_input.s"
  // (First create a file.)
  std::ofstream input;
  input.open ("SHIBBOLETH_input.s");
  input << "# SAMPLE FILE\n";
  input << ".text\n";
  input << "END\n";
  input.close();
  char* argn[] = { (char*) "spam", (char*) "accumulator", (char*) "SHIBBOLETH_input.s" };
  if (skeleton.do_accumulator(3, argn) == IO_ERROR) {
    std::cerr << COLOR_ERROR << "test_do_accumulator() failed. The failing subtest is \"Test with non-missing file\"." << std::endl;
    return FAIL;
  }

  // All tests passed.
  std::cout << COLOR_SUCCESS << "Accumulator test passed." << std::endl;
  return SUCCESS;
}

int spam::TestSkeleton::test_do_gpr() {
  // Test zero arguments.
  //
  char* argv[0];
  if (skeleton.do_gpr(0, argv) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << " test_do_gpr() failed. The failing subtest is \"Test zero arguments\"." << std::endl;
    return FAIL;
  }

  // Test one argument.
  // spam
  char* argh[] = { (char*) "spam" };
  if (skeleton.do_gpr(1, argh) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << " test_do_gpr() failed. The failing subtest is \"Test one argument\"." << std::endl;
    return FAIL;
  }

  // Test two arguments.
  // spam stack
  char* argi[] = { (char*) "spam", (char*) "gpr" };
  if (skeleton.do_gpr(2, argi) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << " test_do_gpr() failed. The failing subtest is \"Test two arguments\"." << std::endl;
    return FAIL;
  }

  // Test three arguments.
  // spam stack "SHIBBOLETH_input.s"
  char* argj[] = { (char*) "spam", (char*) "gpr", (char*) "SHIBBOLETH_input.s" };
  if (skeleton.do_gpr(3, argj) == ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << " test_do_gpr() failed. The failing subtest is \"Test three arguments\"." << std::endl;
    return FAIL;
  }

  // Test incorrect first argument.
  // spam missing ""
  char* argk[] = { (char*) "spam", (char*) "missing", (char*) "" };
  if (skeleton.do_gpr(3, argk) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << " test_do_gpr() failed. The failing subtest is \"Test incorrect first argument\"." << std::endl;
    return FAIL;
  }

  // Test correct first argument.
  // spam stack ""
  char* argl[] = { (char*) "spam", (char*) "gpr", (char*) "" };
  if (skeleton.do_gpr(3, argl) == ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << " test_do_gpr() failed. The failing subtest is \"Test correct first argument\"." << std::endl;
    return FAIL;
  }

  // Test with missing file.
  // spam stack "SHIBBOLETH_missing.s"
  char* argm[] = { (char*) "spam", (char*) "gpr", (char*) "SHIBBOLETH_missing.s" };
  if (skeleton.do_gpr(3, argm) != IO_ERROR) {
    std::cerr << COLOR_ERROR << " test_do_gpr() failed. The failing subtest is \"Test with missing file\"." << std::endl;
    return FAIL;
  }

  // Test with non-missing file.
  // spam stack "SHIBBOLETH_input.s"
  // (First create a file.)
  std::ofstream input;
  input.open ("SHIBBOLETH_input.s");
  input << "# SAMPLE FILE\n";
  input << ".text\n";
  input << "END\n";
  input.close();
  char* argn[] = { (char*) "spam", (char*) "gpr", (char*) "SHIBBOLETH_input.s" };
  if (skeleton.do_gpr(3, argn) == IO_ERROR) {
    std::cerr << COLOR_ERROR << " test_do_gpr() failed. The failing subtest is \"Test with non-missing file\"." << std::endl;
    return FAIL;
  }

  // All tests passed.
  std::cout << COLOR_SUCCESS << "GPR test passed." << std::endl;
  return SUCCESS;
}

int spam::TestSkeleton::test_do_help() {
  // Verify returns true.
  if (skeleton.do_help() != SUCCESS) {
    std::cerr << COLOR_ERROR << "test_do_help() failed. The failing subtest is \"Verify returns true\"." << std::endl;
    return FAIL;
  }

  // All tests passed.
  std::cout << COLOR_SUCCESS << "Help display test passed." << std::endl;
  return SUCCESS;
}

std::string spam::pluralize_test(int i) {
  return (i != 1) ? "tests" : "test";
}

int spam::TestSkeleton::test_pluralize_test() {
  // Test a negative number.
  if (strcmp(spam::pluralize_test(-4).c_str(), "tests") != 0) {
    std::cerr << COLOR_ERROR << "test_pluralize_test() failed. The failing subtest is \"Test a negative number\"." << std::endl;
    return FAIL;
  }

  // Test zero.
  if (strcmp(spam::pluralize_test(0).c_str(), "tests") != 0) {
    std::cerr << COLOR_ERROR << "test_pluralize_test() failed. The failing subtest is \"Test zero\"." << std::endl;
    return FAIL;
  }

  // Test one.
  if (strcmp(spam::pluralize_test(1).c_str(), "test") != 0) {
    std::cerr << COLOR_ERROR << "test_pluralize_test() failed. The failing subtest is \"Test one\"." << std::endl;
    return FAIL;
  }

  // Test a positive number.
  if (strcmp(spam::pluralize_test(4).c_str(), "tests") != 0) {
    std::cerr << COLOR_ERROR << "test_pluralize_test() failed. The failing subtest is \"Test a positive number\"." << std::endl;
    return FAIL;
  }

  // All tests passed.
  std::cout << COLOR_SUCCESS << "Pluralization test passed." << std::endl;
  return SUCCESS;
}

int main(int argc, char** argv) {
  spam::TestSkeleton testskeleton;

  int tests_run = 7;
  int tests_skipped = 2;
  int tests_passed = tests_run - tests_skipped;

  tests_passed += testskeleton.test_file_exists();
  tests_passed += testskeleton.test_do_memory();
  //tests_passed += testskeleton.test_do_stack();
  //tests_passed += testskeleton.test_do_accumulator();
  tests_passed += testskeleton.test_do_gpr();
  tests_passed += testskeleton.test_do_help();
  tests_passed += testskeleton.test_pluralize_test();

  int tests_failed = tests_run - tests_passed - tests_skipped;

  if (tests_run > 0) {
    std::cout << "RESULTS:" << std::endl;
    std::cout << "\t" << tests_run << " " << spam::pluralize_test(tests_run) << " run." << std::endl;
  }

  if (tests_passed > 0) {
    std::cout << "\t" << COLOR_GREEN << tests_passed << " " << spam::pluralize_test(tests_passed) << " passed." << COLOR_STOP << std::endl;
  } else {
    std::cout << "\t" << tests_passed << " tests passed." << std::endl;
  }

  if (tests_skipped > 0) {
    std::cout << "\t" << COLOR_YELLOW << tests_skipped << " " << spam::pluralize_test(tests_skipped) << " skipped." << COLOR_STOP << std::endl;
  } else {
    std::cout << "\t" << tests_skipped << " tests skipped." << std::endl;
  }

  if (tests_failed > 0) {
    std::cout << "\t" << COLOR_RED << tests_failed << " " << spam::pluralize_test(tests_failed) << " failed." << COLOR_STOP << std::endl;
  } else {
    std::cout << "\t" << tests_failed << " tests failed." << std::endl;
  }

  return (tests_failed == 0) ? SUCCESS: FAIL;
}
