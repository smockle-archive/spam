#include "test.hpp"

spam::TestGPR::TestGPR() {
}

int spam::TestGPR::test_gpr_addi() {
  // Tests failed. Tests have not been written yet.
  std::cout << COLOR_ERROR << " test_gpr_addi() failed. Tests have not been written yet." << std::endl;
  return FAIL;
}

int spam::TestGPR::test_gpr_b() {
  // Tests failed. Tests have not been written yet.
  std::cout << COLOR_ERROR << " test_gpr_b() failed. Tests have not been written yet." << std::endl;
  return FAIL;
}

int spam::TestGPR::test_gpr_beqz() {
  // Tests failed. Tests have not been written yet.
  std::cout << COLOR_ERROR << " test_gpr_beqz() failed. Tests have not been written yet." << std::endl;
  return FAIL;
}

int spam::TestGPR::test_gpr_bge() {
  // Tests failed. Tests have not been written yet.
  std::cout << COLOR_ERROR << " test_gpr_bge() failed. Tests have not been written yet." << std::endl;
  return FAIL;
}

int spam::TestGPR::test_gpr_bne() {
  // Tests failed. Tests have not been written yet.
  std::cout << COLOR_ERROR << " test_gpr_bne() failed. Tests have not been written yet." << std::endl;
  return FAIL;
}

int spam::TestGPR::test_gpr_la() {
  // Tests failed. Tests have not been written yet.
  std::cout << COLOR_ERROR << " test_gpr_la() failed. Tests have not been written yet." << std::endl;
  return FAIL;
}

int spam::TestGPR::test_gpr_lb() {
  // Tests failed. Tests have not been written yet.
  std::cout << COLOR_ERROR << " test_gpr_lb() failed. Tests have not been written yet." << std::endl;
  return FAIL;
}

int spam::TestGPR::test_gpr_li() {
  // Tests failed. Tests have not been written yet.
  std::cout << COLOR_ERROR << " test_gpr_li() failed. Tests have not been written yet." << std::endl;
  return FAIL;
}

int spam::TestGPR::test_gpr_subi() {
  // Tests failed. Tests have not been written yet.
  std::cout << COLOR_ERROR << " test_gpr_subi() failed. Tests have not been written yet." << std::endl;
  return FAIL;
}

int spam::TestGPR::test_gpr_syscall() {
  // Tests failed. Tests have not been written yet.
  std::cout << COLOR_ERROR << " test_gpr_syscall() failed. Tests have not been written yet." << std::endl;
  return FAIL;
}

int spam::TestGPR::test_gpr_decode_label() {
  // Tests failed. Tests have not been written yet.
  std::cout << COLOR_ERROR << " test_gpr_decode_label() failed. Tests have not been written yet." << std::endl;
  return FAIL;
}

int spam::TestGPR::test_gpr_end() {
  // Tests failed. Tests have not been written yet.
  std::cout << COLOR_ERROR << " test_gpr_end() failed. Tests have not been written yet." << std::endl;
  return FAIL;
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
