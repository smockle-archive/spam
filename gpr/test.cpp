#include "test.hpp"

// I consulted the following resources for help:
// https://answers.yahoo.com/question/index?qid=20060826004427AARjJ2q

spam::TestGPR::TestGPR() {
}

int spam::TestGPR::test_gpr_addi() {
  // Test negative source address with postive destination address.
  if (gpr.addi(-4) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << " test_accumulator_load() failed. The failing subtest is \"Test negative address\"." << std::endl;
    return FAIL;
  }

  // Test negative destination address with positive source address.

  // Test positive source address outside range. 31. with positive destination address.

  // Test positive destination address outside range. 31. with positive source address.

  // Test negative immediate value outside range. -32,768

  // Test positive immediate value outside range. 32,767

  // Test positive source address, positive destination address, immediate value in range, sum exceeds range.

  // Test positive source address, positive destination address, immediate value in range, sum in range.
    // Does function succeed?
    // Is sum correct?

  // Tests failed. Tests have not been written yet.
  std::cout << COLOR_ERROR << " test_gpr_b() failed. Tests have not been written yet." << std::endl;
  return FAIL;

  // All tests passed.
  std::cout << COLOR_SUCCESS << " test_accumulator_end() passed." << std::endl;
  return SUCCESS;
}

int spam::TestGPR::test_gpr_b() {
  // Test label which doesn't exist.

  // Test label which does exist.
    // Does function succeed?
    // Did the value of PC change?

  // Tests failed. Tests have not been written yet.
  std::cout << COLOR_ERROR << " test_gpr_b() failed. Tests have not been written yet." << std::endl;
  return FAIL;

  // All tests passed.
  std::cout << COLOR_SUCCESS << " test_accumulator_end() passed." << std::endl;
  return SUCCESS;
}

int spam::TestGPR::test_gpr_beqz() {
  // Test negative register address.

  // Test positive register address outside range. 31

  // Test label which doesn't exist.

  // Test label which does exist, value at register is not zero.
    // Does the function succeed?
    // Did the value of PC stay the same?

  // Test label which does exist, value at register is zero.
    // Does function succeed?
    // Did the value of PC change?

  // Tests failed. Tests have not been written yet.
  std::cout << COLOR_ERROR << " test_gpr_beqz() failed. Tests have not been written yet." << std::endl;
  return FAIL;

  // All tests passed.
  std::cout << COLOR_SUCCESS << " test_accumulator_end() passed." << std::endl;
  return SUCCESS;
}

int spam::TestGPR::test_gpr_bge() {
  // Test negative source address with postive destination address.

  // Test negative destination address with postive source address.

  // Test positive source address outside range. 31. with positive destination address.

  // Test positive destination address outside range. 31. with positive source address.

  // Test label which doesn't exist.

  // Test label which does exist, value at source is less than destination.
    // Does the function succeed?
    // Did the value of PC stay the same?

  // Test label which does exist, value at source is equal to destination.
    // Does the function succeed?
    // Did the value of PC change?

  // Test label which does exist, value at source is greater than destination.
    // Does the function succeed?
    // Did the value of PC change?

  // Tests failed. Tests have not been written yet.
  std::cout << COLOR_ERROR << " test_gpr_bge() failed. Tests have not been written yet." << std::endl;
  return FAIL;

  // All tests passed.
  std::cout << COLOR_SUCCESS << " test_accumulator_end() passed." << std::endl;
  return SUCCESS;
}

int spam::TestGPR::test_gpr_bne() {
  // Test negative source address with postive destination address.

  // Test negative destination address with postive source address.

  // Test positive source address outside range. 31. with positive destination address.

  // Test positive destination address outside range. 31. with positive source address.

  // Test label which doesn't exist.

  // Test label which does exist, value at source is equal to destination.
    // Does the function succeed?
    // Did the value of PC stay the same?

  // Test label which does exist, value at source is not equal to destination.
    // Does the function succeed?
    // Did the value of PC change?

  // Tests failed. Tests have not been written yet.
  std::cout << COLOR_ERROR << " test_gpr_bne() failed. Tests have not been written yet." << std::endl;
  return FAIL;

  // All tests passed.
  std::cout << COLOR_SUCCESS << " test_accumulator_end() passed." << std::endl;
  return SUCCESS;
}

int spam::TestGPR::test_gpr_la() {
  // Test negative register address.

  // Test positive register address outside range. 31

  // Test variable name which doesn't exist.

  // Test variable name which does exist, value of variable is too big for register.

  // Test label which does exist, value of variable fits in register.
    // Does function succeed?
    // Did register contain value of variable?

  // Tests failed. Tests have not been written yet.
  std::cout << COLOR_ERROR << " test_gpr_la() failed. Tests have not been written yet." << std::endl;
  return FAIL;
}

int spam::TestGPR::test_gpr_lb() {
  // TODO: Write tests for gpr.lb().

  // Tests failed. Tests have not been written yet.
  std::cout << COLOR_ERROR << " test_gpr_lb() failed. Tests have not been written yet." << std::endl;
  return FAIL;

  // All tests passed.
  std::cout << COLOR_SUCCESS << " test_accumulator_end() passed." << std::endl;
  return SUCCESS;
}

int spam::TestGPR::test_gpr_li() {
  // Test negative register address.

  // Test positive register address outside range. 31

  // Test negative immediate value outside range. -32,768

  // Test positive immediate value outside range. 32,767

  // Test valid register address, immediate value fits in register.
    // Does function succeed?
    // Did register contain immediate value?

  // Tests failed. Tests have not been written yet.
  std::cout << COLOR_ERROR << " test_gpr_li() failed. Tests have not been written yet." << std::endl;
  return FAIL;

  // All tests passed.
  std::cout << COLOR_SUCCESS << " test_accumulator_end() passed." << std::endl;
  return SUCCESS;
}

int spam::TestGPR::test_gpr_subi() {
  // Test negative source address with postive destination address.

  // Test negative destination address with positive source address.

  // Test positive source address outside range. 31. with positive destination address.

  // Test positive destination address outside range. 31. with positive source address.

  // Test negative immediate value outside range. -32,768

  // Test positive immediate value outside range. 32,767

  // Test positive source address, positive destination address, immediate value in range, difference exceeds range.

  // Test positive source address, positive destination address, immediate value in range, difference in range.
    // Does function succeed?
    // Is difference correct?

  // Tests failed. Tests have not been written yet.
  std::cout << COLOR_ERROR << " test_gpr_subi() failed. Tests have not been written yet." << std::endl;
  return FAIL;

  // All tests passed.
  std::cout << COLOR_SUCCESS << " test_accumulator_end() passed." << std::endl;
  return SUCCESS;
}

int spam::TestGPR::test_gpr_syscall() {
  // Test reading console input. ($V0 contains 8)
  gpr.registry.store(V0_ADDR, SYSCALL_CIN);
  if (gpr.syscall() != SYSCALL_CIN) {
    return FAIL;
  }

  // Test writing console output. ($V0 contains 4)
  gpr.registry.store(V0_ADDR, SYSCALL_COUT);
  if (gpr.syscall() != SYSCALL_COUT) {
    return FAIL;
  }

  // Test program termination. ($V0 contains 10)
  gpr.registry.store(V0_ADDR, SYSCALL_END);
  if (gpr.syscall() != SYSCALL_END) {
    return FAIL;
  }

  // All tests passed.
  std::cout << COLOR_SUCCESS << " test_accumulator_end() passed." << std::endl;
  return SUCCESS;
}

int spam::TestGPR::test_gpr_decode_label() {
  // TODO: Write tests for gpr.decode_label().

  // Tests failed. Tests have not been written yet.
  std::cout << COLOR_ERROR << " test_gpr_decode_label() failed. Tests have not been written yet." << std::endl;
  return FAIL;

  // All tests passed.
  std::cout << COLOR_SUCCESS << " test_accumulator_end() passed." << std::endl;
  return SUCCESS;
}

int spam::TestGPR::test_gpr_end() {
  // Verify returns true.
  if (gpr.end() != SUCCESS) {
    std::cerr << COLOR_ERROR << " test_gpr_end() failed. The failing subtest is \"Verify returns true\"." << std::endl;
    return FAIL;
  }

  // All tests passed.
  std::cout << COLOR_SUCCESS << " test_gpr_end() passed." << std::endl;
  return SUCCESS;
}

int main(int argc, char** argv) {
  spam::TestGPR testgpr;

  int tests_run = 12;
  int tests_passed = 12;

  tests_passed += testgpr.test_gpr_addi();
  tests_passed += testgpr.test_gpr_b();
  tests_passed += testgpr.test_gpr_beqz();
  tests_passed += testgpr.test_gpr_bge();
  tests_passed += testgpr.test_gpr_bne();
  tests_passed += testgpr.test_gpr_la();
  tests_passed += testgpr.test_gpr_lb();
  tests_passed += testgpr.test_gpr_li();
  tests_passed += testgpr.test_gpr_subi();
  tests_passed += testgpr.test_gpr_syscall();
  tests_passed += testgpr.test_gpr_decode_label();
  tests_passed += testgpr.test_gpr_end();

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
