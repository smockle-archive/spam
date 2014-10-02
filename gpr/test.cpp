#include "test.hpp"

// I consulted the following resources for help:
// https://answers.yahoo.com/question/index?qid=20060826004427AARjJ2q

spam::TestGPR::TestGPR() {
}

int spam::TestGPR::test_gpr_addi() {
  // Test negative source address.
  if (gpr.addi(0, -1, 1) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_gpr_addi() failed. The failing subtest is \"Test negative source address\"." << std::endl;
    return FAIL;
  }

  // Test negative destination address.
  if (gpr.addi(-1, 0, 1) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_gpr_addi() failed. The failing subtest is \"Test negative destination address\"." << std::endl;
    return FAIL;
  }

  // Test positive source address outside range (>31).
  if (gpr.addi(0, 32, 1) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_gpr_addi() failed. The failing subtest is \"Test positive source address outside range (>31)\"." << std::endl;
    return FAIL;
  }

  // Test positive destination address outside range (>31).
  if (gpr.addi(32, 0, 1) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_gpr_addi() failed. The failing subtest is \"Test positive destination address outside range (>31)\"." << std::endl;
    return FAIL;
  }

  // Test negative immediate value outside range (<-32,768).
  if (gpr.addi(0, 0, -32769) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_gpr_addi() failed. The failing subtest is \"Test negative immediate value outside range (<-32,768)\"." << std::endl;
    return FAIL;
  }

  // Test positive immediate value outside range (>32,767).
  if (gpr.addi(0, 0, 32770) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_gpr_addi() failed. The failing subtest is \"Test negative immediate value outside range (>32,769)\"." << std::endl;
    return FAIL;
  }

  // Test sum exceeds range.
  gpr.registry.store(0, 32000);
  if (gpr.addi(1, 0, 32000) != VALUE_ERROR) {
    std::cerr << COLOR_ERROR << "test_gpr_addi() failed. The failing subtest is \"Test sum exceeds range\"." << std::endl;
    return FAIL;
  }

  // Test sum in range for success.
  gpr.registry.store(0, 1);
  if (gpr.addi(1, 0, 1) != SUCCESS) {
    std::cerr << COLOR_ERROR << "test_gpr_addi() failed. The failing subtest is \"Test sum in range for success\"." << std::endl;
    return FAIL;
  }

  // Test sum in range for correctness.
  gpr.registry.store(0, 1);
  gpr.addi(1, 0, 1);
  if (gpr.registry.load(0) != 2) {
    std::cerr << COLOR_ERROR << "test_gpr_addi() failed. The failing subtest is \"Test sum in range for correctness\"." << std::endl;
    return FAIL;
  }

  // All tests passed.
  std::cout << COLOR_SUCCESS << "test_gpr_addi() passed." << std::endl;
  return SUCCESS;
}

int spam::TestGPR::test_gpr_b() {
  // TODO: Write tests for gpr.b().

  // Test negative label address.
  if (gpr.b(-1) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_gpr_b() failed. The failing subtest is \"Test negative label address\"." << std::endl;
    return FAIL;
  }

  // Test positive label address outside range (<512 or >=768).
  if (gpr.b(1) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_gpr_b() failed. The failing subtest is \"Test positive label address outside range (<256 or >=512)\"." << std::endl;
    return FAIL;
  }

  // Test valid label address for success.
  if (gpr.b(T_BASE_ADDR) != SUCCESS) {
    std::cerr << COLOR_ERROR << "test_gpr_b() failed. The failing subtest is \"Test valid label address for success\"." << std::endl;
    return FAIL;
  }

  // Test valid label address, verify PC value changed.
  gpr.pc = 1;
  gpr.b(T_BASE_ADDR);
  if (gpr.pc != T_BASE_ADDR) {
    std::cerr << COLOR_ERROR << "test_gpr_b() failed. The failing subtest is \"Test valid label address, verify PC value changed\"." << std::endl;
    return FAIL;
  }

  // All tests passed.
  std::cout << COLOR_SUCCESS << "test_gpr_b() passed." << std::endl;
  return SUCCESS;
}

int spam::TestGPR::test_gpr_beqz() {
  // TODO: Write tests for gpr.beqz().

  // Test negative register address.
  if (gpr.beqz(-1, (char *) "SHIBBOLETH_missing") != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_gpr_beqz() failed. The failing subtest is \"Test negative register address\"." << std::endl;
    return FAIL;
  }

  // Test positive register address outside range (>31).
  if (gpr.beqz(32, (char *) "SHIBBOLETH_missing") != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_gpr_beqz() failed. The failing subtest is \"Test positive register address outside range (>31)\"." << std::endl;
    return FAIL;
  }

  // Test negative label address.

  // Test positive label address outside range (<256 || >=512).

  // Test valid label address, value at register is not zero for success.

  // Test valid label address, value at register is not zero, verify PC value didn't change.

  // Test valid label address, value at register is zero for success.

  // Test valid label address, value at register is zero, verify PC value changed?

  // Tests failed. Tests have not been written yet.
  std::cout << COLOR_ERROR << "test_gpr_beqz() failed. Tests have not been written yet." << std::endl;
  return FAIL;

  // All tests passed.
  std::cout << COLOR_SUCCESS << "test_gpr_beqz() passed." << std::endl;
  return SUCCESS;
}

int spam::TestGPR::test_gpr_bge() {
  // TODO: Write tests for gpr.bge().

  // Test negative source address.

  // Test negative destination address.

  // Test positive source address outside range (>31).

  // Test positive destination address outside range (>31).

  // Test negative label address.

  // Test positive label address outside range (<256 || >=512).

  // Test valid label address, value at source is less than destination for success.

  // Test valid label address, value at source is less than destination, verify PC value didn't change.

  // Test valid label address, value at source is equal to destination for success.

  // Test valid label address, value at source is equal to destination, verify PC value changed.

  // Test valid label address, value at source is greater than destination for success.

  // Test valid label address, value at source is greater than destination, verify PC value changed.

  // Tests failed. Tests have not been written yet.
  std::cout << COLOR_ERROR << "test_gpr_bge() failed. Tests have not been written yet." << std::endl;
  return FAIL;

  // All tests passed.
  std::cout << COLOR_SUCCESS << "test_gpr_bge() passed." << std::endl;
  return SUCCESS;
}

int spam::TestGPR::test_gpr_bne() {
  // TODO: Write tests for gpr.bne().

  // Test negative source address with postive destination address.

  // Test negative destination address with postive source address.

  // Test positive source address outside range (>31).

  // Test positive destination address outside range (>31).

  // Test negative label address.

  // Test positive label address outside range (<256 || >=512).

  // Test valid label address, value at source is equal to destination for success.

  // Test valid label address, value at source is equal to destination, verify PC value didn't change.

  // Test valid label address, value at source is not equal to destination for success.

  // Test valid label address, value at source is not equal to destination, verify PC value changed.

  // Tests failed. Tests have not been written yet.
  std::cout << COLOR_ERROR << "test_gpr_bne() failed. Tests have not been written yet." << std::endl;
  return FAIL;

  // All tests passed.
  std::cout << COLOR_SUCCESS << "test_gpr_bne() passed." << std::endl;
  return SUCCESS;
}

int spam::TestGPR::test_gpr_la() {
  // TODO: Write tests for gpr.la().

  // Test negative register address.

  // Test positive register address outside range (>31).

  // Test variable name which doesn't exist.

  // Test variable name which does exist, value of variable is too big for register.

  // Test negative variable address.

  // Test positive variable address outside range (<256 || >=512).

  // Test valid variable address, value of variable fits in register for success.

  // Test valid variable address, value of variable fits in register, verify register contains value of variable.

  // Tests failed. Tests have not been written yet.
  std::cout << COLOR_ERROR << "test_gpr_la() failed. Tests have not been written yet." << std::endl;
  return FAIL;
}

int spam::TestGPR::test_gpr_lb() {
  // TODO: Write tests for gpr.lb().

  // Tests failed. Tests have not been written yet.
  std::cout << COLOR_ERROR << "test_gpr_lb() failed. Tests have not been written yet." << std::endl;
  return FAIL;

  // All tests passed.
  std::cout << COLOR_SUCCESS << "test_gpr_lb() passed." << std::endl;
  return SUCCESS;
}

int spam::TestGPR::test_gpr_li() {
  // TODO: Write tests for gpr.li().

  // Test negative register address.

  // Test positive register address outside range (>31).

  // Test negative immediate value outside range (<-32,768).

  // Test positive immediate value outside range (>32,767).

  // Test valid register address, immediate value fits in register for success.

  // Test valid register address, immediate value fits in register, verify register contains immediate value.

  // Tests failed. Tests have not been written yet.
  std::cout << COLOR_ERROR << "test_gpr_li() failed. Tests have not been written yet." << std::endl;
  return FAIL;

  // All tests passed.
  std::cout << COLOR_SUCCESS << "test_gpr_li() passed." << std::endl;
  return SUCCESS;
}

int spam::TestGPR::test_gpr_subi() {
  // TODO: Write tests for gpr.subi().

  // Test negative source address with postive destination address.

  // Test negative destination address with positive source address.

  // Test positive source address outside range (>31).

  // Test positive destination address outside range (>31).

  // Test negative immediate value outside range (<-32,768).

  // Test positive immediate value outside range (>32,767).

  // Test difference exceeds range.

  // Test difference in range for success.

  // Test difference in range for correctness.

  // Tests failed. Tests have not been written yet.
  std::cout << COLOR_ERROR << "test_gpr_subi() failed. Tests have not been written yet." << std::endl;
  return FAIL;

  // All tests passed.
  std::cout << COLOR_SUCCESS << "test_gpr_subi() passed." << std::endl;
  return SUCCESS;
}

int spam::TestGPR::test_gpr_syscall() {
  // Test reading console input. ($V0 contains 8)
  gpr.registry.store(V0_ADDR, SYSCALL_CIN);
  if (gpr.syscall() != SYSCALL_CIN) {
    std::cerr << COLOR_ERROR << "test_gpr_syscall() failed. The failing subtest is \"Test reading console input\"." << std::endl;
    return FAIL;
  }

  // Test writing console output. ($V0 contains 4)
  gpr.registry.store(V0_ADDR, SYSCALL_COUT);
  if (gpr.syscall() != SYSCALL_COUT) {
    std::cerr << COLOR_ERROR << "test_gpr_syscall() failed. The failing subtest is \"Test writing console output\"." << std::endl;
    return FAIL;
  }

  // Test program termination. ($V0 contains 10)
  gpr.registry.store(V0_ADDR, SYSCALL_END);
  if (gpr.syscall() != SYSCALL_END) {
    std::cerr << COLOR_ERROR << "test_gpr_syscall() failed. The failing subtest is \"Test program termination\"." << std::endl;
    return FAIL;
  }

  // All tests passed.
  std::cout << COLOR_SUCCESS << "test_gpr_syscall() passed." << std::endl;
  return SUCCESS;
}

int spam::TestGPR::test_gpr_end() {
  // Verify returns true.
  if (gpr.end() != SUCCESS) {
    std::cerr << COLOR_ERROR << "test_gpr_end() failed. The failing subtest is \"Verify returns true\"." << std::endl;
    return FAIL;
  }

  // All tests passed.
  std::cout << COLOR_SUCCESS << "test_gpr_end() passed." << std::endl;
  return SUCCESS;
}

int main(int argc, char** argv) {
  spam::TestGPR testgpr;

  int tests_run = 11;
  int tests_passed = 11;

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
