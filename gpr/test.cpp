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
  if (gpr.addi(0, 0, MIN_IMMEDIATE-1) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_gpr_addi() failed. The failing subtest is \"Test negative immediate value outside range (<-32,768)\"." << std::endl;
    return FAIL;
  }

  // Test positive immediate value outside range (>32,767).
  if (gpr.addi(0, 0, MAX_IMMEDIATE+1) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_gpr_addi() failed. The failing subtest is \"Test negative immediate value outside range (>32,769)\"." << std::endl;
    return FAIL;
  }

  // Test sum exceeds range.
  gpr.registry.store(0, MAX_IMMEDIATE-1);
  if (gpr.addi(1, 0, MAX_IMMEDIATE-1) != VALUE_ERROR) {
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
  if (gpr.registry.load(1) != 2) {
    std::cerr << COLOR_ERROR << "test_gpr_addi() failed. The failing subtest is \"Test sum in range for correctness\"." << std::endl;
    return FAIL;
  }

  // All tests passed.
  std::cout << COLOR_SUCCESS << "test_gpr_addi() passed." << std::endl;
  return SUCCESS;
}

int spam::TestGPR::test_gpr_b() {
  // Test negative label address.
  if (gpr.b(-1) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_gpr_b() failed. The failing subtest is \"Test negative label address\"." << std::endl;
    return FAIL;
  }

  // Test positive label address outside range (<512 or >=768).
  if (gpr.b(1) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_gpr_b() failed. The failing subtest is \"Test positive label address outside range (<512 or >=768)\"." << std::endl;
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
  // Test negative register address.
  if (gpr.beqz(-1, T_BASE_ADDR) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_gpr_beqz() failed. The failing subtest is \"Test negative register address\"." << std::endl;
    return FAIL;
  }

  // Test positive register address outside range (>31).
  if (gpr.beqz(32, T_BASE_ADDR) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_gpr_beqz() failed. The failing subtest is \"Test positive register address outside range (>31)\"." << std::endl;
    return FAIL;
  }

  // Test negative label address.
  if (gpr.beqz(0, -1) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_gpr_beqz() failed. The failing subtest is \"Test negative label address\"." << std::endl;
    return FAIL;
  }

  // Test positive label address outside range (<512 or >=768).
  if (gpr.beqz(0, 1) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_gpr_beqz() failed. The failing subtest is \"Test positive label address outside range (<512 or >=768)\"." << std::endl;
    return FAIL;
  }

  // Test valid label address, value at register is not zero for success.
  gpr.registry.store(0, 1);
  if (gpr.beqz(0, T_BASE_ADDR) != SUCCESS) {
    std::cerr << COLOR_ERROR << "test_gpr_beqz() failed. The failing subtest is \"Test valid label address, value at register is not zero for success\"." << std::endl;
    return FAIL;
  }

  // Test valid label address, value at register is not zero, verify PC value didn't change.
  gpr.registry.store(0, 1);
  gpr.pc = 1;
  gpr.beqz(0, T_BASE_ADDR);
  if (gpr.pc != 1) {
    std::cerr << COLOR_ERROR << "test_gpr_beqz() failed. The failing subtest is \"Test valid label address, value at register is not zero, verify PC value didn't change\"." << std::endl;
    return FAIL;
  }

  // Test valid label address, value at register is zero for success.
  gpr.registry.store(0, 0);
  if (gpr.beqz(0, T_BASE_ADDR) != SUCCESS) {
    std::cerr << COLOR_ERROR << "test_gpr_beqz() failed. The failing subtest is \"Test valid label address, value at register is zero for success\"." << std::endl;
    return FAIL;
  }

  // Test valid label address, value at register is zero, verify PC value changed.
  gpr.registry.store(0, 0);
  gpr.pc = 1;
  gpr.beqz(0, T_BASE_ADDR);
  if (gpr.pc != 1) {
    std::cerr << COLOR_ERROR << "test_gpr_beqz() failed. The failing subtest is \"Test valid label address, value at register is not zero, verify PC changed\"." << std::endl;
    return FAIL;
  }

  // All tests passed.
  std::cout << COLOR_SUCCESS << "test_gpr_beqz() passed." << std::endl;
  return SUCCESS;
}

int spam::TestGPR::test_gpr_bge() {
  // Test negative register1 address.
  if (gpr.bge(-1, 1, T_BASE_ADDR) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_gpr_bge() failed. The failing subtest is \"Test negative register1 address\"." << std::endl;
    return FAIL;
  }

  // Test negative register2 address.
  if (gpr.bge(1, -1, T_BASE_ADDR) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_gpr_bge() failed. The failing subtest is \"Test negative register2 address\"." << std::endl;
    return FAIL;
  }

  // Test positive register1 address outside range (>31).
  if (gpr.bge(32, 1, T_BASE_ADDR) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_gpr_bge() failed. The failing subtest is \"Test positive register1 address outside range (>31)\"." << std::endl;
    return FAIL;
  }

  // Test positive register2 address outside range (>31).
  if (gpr.bge(1, 32, T_BASE_ADDR) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_gpr_bge() failed. The failing subtest is \"Test positive register2 address outside range (>31)\"." << std::endl;
    return FAIL;
  }

  // Test negative label address.
  if (gpr.bge(0, 1, -1) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_gpr_bge() failed. The failing subtest is \"Test negative label address\"." << std::endl;
    return FAIL;
  }

  // Test positive label address outside range (<512 or >=768).
  if (gpr.bge(0, 1, 1) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_gpr_bge() failed. The failing subtest is \"Test positive label address outside range (<512 or >=768)\"." << std::endl;
    return FAIL;
  }

  // Test valid label address, value at register1 is less than value at register2 for success.
  gpr.registry.store(0, 10);
  gpr.registry.store(1, 20);
  if (gpr.bge(0, 1, T_BASE_ADDR) != SUCCESS) {
    std::cerr << COLOR_ERROR << "test_gpr_bge() failed. The failing subtest is \"Test valid label address, value at register1 is less than value at register2 for success\"." << std::endl;
    return FAIL;
  }

  // Test valid label address, value at register1 is less than value at register2, verify PC value didn't change.
  gpr.registry.store(0, 10);
  gpr.registry.store(1, 20);
  gpr.pc = 1;
  gpr.bge(0, 1, T_BASE_ADDR);
  if (gpr.pc != 1) {
    std::cerr << COLOR_ERROR << "test_gpr_bge() failed. The failing subtest is \"Test valid label address, value at register1 is less than value at register2, verify PC value didn't change\"." << std::endl;
    return FAIL;
  }

  // Test valid label address, value at register1 is equal to value at register2 for success.
  gpr.registry.store(0, 10);
  gpr.registry.store(1, 10);
  if (gpr.bge(0, 1, T_BASE_ADDR) != SUCCESS) {
    std::cerr << COLOR_ERROR << "test_gpr_bge() failed. The failing subtest is \"Test valid label address, value at register1 is equal to value at register2 for success\"." << std::endl;
    return FAIL;
  }

  // Test valid label address, value at register1 is equal to value at register2, verify PC value changed.
  gpr.registry.store(0, 10);
  gpr.registry.store(1, 10);
  gpr.pc = 1;
  gpr.bge(0, 1, T_BASE_ADDR);
  if (gpr.pc != T_BASE_ADDR) {
    std::cerr << COLOR_ERROR << "test_gpr_bge() failed. The failing subtest is \"Test valid label address, value at register1 is equal to value at register2, verify PC value changed\"." << std::endl;
    return FAIL;
  }

  // Test valid label address, value at register1 is greater than value at register2 for success.
  gpr.registry.store(0, 20);
  gpr.registry.store(1, 10);
  if (gpr.bge(0, 1, T_BASE_ADDR) != SUCCESS) {
    std::cerr << COLOR_ERROR << "test_gpr_bge() failed. The failing subtest is \"Test valid label address, value at register1 is greater than value at register2 for success\"." << std::endl;
    return FAIL;
  }

  // Test valid label address, value at register1 is greater than value at register2, verify PC value changed.
  gpr.registry.store(0, 20);
  gpr.registry.store(1, 10);
  gpr.pc = 1;
  gpr.bge(0, 1, T_BASE_ADDR);
  if (gpr.pc != T_BASE_ADDR) {
    std::cerr << COLOR_ERROR << "test_gpr_bge() failed. The failing subtest is \"Test valid label address, value at register1 is greater than value at register2, verify PC value changed\"." << std::endl;
    return FAIL;
  }

  // All tests passed.
  std::cout << COLOR_SUCCESS << "test_gpr_bge() passed." << std::endl;
  return SUCCESS;
}

int spam::TestGPR::test_gpr_bne() {
  // Test negative register1 address.
  if (gpr.bne(-1, 1, T_BASE_ADDR) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_gpr_bne() failed. The failing subtest is \"Test negative register1 address\"." << std::endl;
    return FAIL;
  }

  // Test negative register2 address.
  if (gpr.bne(1, -1, T_BASE_ADDR) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_gpr_bne() failed. The failing subtest is \"Test negative register2 address\"." << std::endl;
    return FAIL;
  }

  // Test positive register1 address outside range (>31).
  if (gpr.bne(32, 1, T_BASE_ADDR) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_gpr_bne() failed. The failing subtest is \"Test positive register1 address outside range (>31)\"." << std::endl;
    return FAIL;
  }

  // Test positive register2 address outside range (>31).
  if (gpr.bne(1, 32, T_BASE_ADDR) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_gpr_bne() failed. The failing subtest is \"Test positive register2 address outside range (>31)\"." << std::endl;
    return FAIL;
  }

  // Test negative label address.
  if (gpr.bne(0, 1, -1) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_gpr_bne() failed. The failing subtest is \"Test negative label address\"." << std::endl;
    return FAIL;
  }

  // Test positive label address outside range (<512 or >=768).
  if (gpr.bne(0, 1, 1) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_gpr_bne() failed. The failing subtest is \"Test positive label address outside range (<512 or >=768)\"." << std::endl;
    return FAIL;
  }

  // Test valid label address, value at register1 is equal to value at register2 for success.
  gpr.registry.store(0, 10);
  gpr.registry.store(1, 10);
  if (gpr.bne(0, 1, T_BASE_ADDR) != SUCCESS) {
    std::cerr << COLOR_ERROR << "test_gpr_bne() failed. The failing subtest is \"Test valid label address, value at register1 is equal to value at register2 for success\"." << std::endl;
    return FAIL;
  }

  // Test valid label address, value at register1 is equal to value at register2, verify PC value didn't change.
  gpr.registry.store(0, 10);
  gpr.registry.store(1, 10);
  gpr.pc = 1;
  gpr.bne(0, 1, T_BASE_ADDR);
  if (gpr.pc != 1) {
    std::cerr << COLOR_ERROR << "test_gpr_bne() failed. The failing subtest is \"Test valid label address, value at register1 is equal to value at register2, verify PC value didn't change\"." << std::endl;
    return FAIL;
  }

  // Test valid label address, value at register1 is not equal to value at register2 for success.
  gpr.registry.store(0, 10);
  gpr.registry.store(1, 20);
  if (gpr.bne(0, 1, T_BASE_ADDR) != SUCCESS) {
    std::cerr << COLOR_ERROR << "test_gpr_bne() failed. The failing subtest is \"Test valid label address, value at register1 is not equal to value at register2 for success\"." << std::endl;
    return FAIL;
  }

  // Test valid label address, value at register1 is not equal to value at register2, verify PC value changed.
  gpr.registry.store(0, 10);
  gpr.registry.store(1, 20);
  gpr.pc = 1;
  gpr.bne(0, 1, T_BASE_ADDR);
  if (gpr.pc != T_BASE_ADDR) {
    std::cerr << COLOR_ERROR << "test_gpr_bne() failed. The failing subtest is \"Test valid label address, value at register1 is not equal to value at register2, verify PC value changed\"." << std::endl;
    return FAIL;
  }

  // All tests passed.
  std::cout << COLOR_SUCCESS << "test_gpr_bne() passed." << std::endl;
  return SUCCESS;
}

int spam::TestGPR::test_gpr_la() {
  // Test negative register address.
  if (gpr.la(-1, 1) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_gpr_la() failed. The failing subtest is \"Test negative register address\"." << std::endl;
    return FAIL;
  }

  // Test positive register address outside range (>31).
  if (gpr.la(32, 1) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_gpr_la() failed. The failing subtest is \"Test positive register address outside range (>31)\"." << std::endl;
    return FAIL;
  }

  // Test negative variable address.
  if (gpr.la(1, -1) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_gpr_la() failed. The failing subtest is \"Test negative variable address\"." << std::endl;
    return FAIL;
  }

  // Test positive variable address outside range (<256 or >=512).
  if (gpr.la(1, 1) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_gpr_la() failed. The failing subtest is \"Test positive variable address outside range (<256 or >=512)\"." << std::endl;
    return FAIL;
  }

  // Test valid variable address for success.
  if (gpr.la(1, D_BASE_ADDR) != SUCCESS) {
    std::cerr << COLOR_ERROR << "test_gpr_la() failed. The failing subtest is \"Test valid variable address for success\"." << std::endl;
    return FAIL;
  }

  // Test valid variable address, verify register contains value of variable.
  gpr.registry.store(1, 1);
  gpr.la(1, D_BASE_ADDR);
  if (gpr.registry.load(1) != D_BASE_ADDR) {
    std::cerr << COLOR_ERROR << "test_gpr_la() failed. The failing subtest is \"Test valid variable address for success\"." << std::endl;
    return FAIL;
  }

  // All tests passed.
  std::cout << COLOR_SUCCESS << "test_gpr_la() passed." << std::endl;
  return SUCCESS;
}

int spam::TestGPR::test_gpr_lb() {
  // Test negative source register address.
  if (gpr.lb(1, 1, -1) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_gpr_lb() failed. The failing subtest is \"Test negative source register address\"." << std::endl;
    return FAIL;
  }

  // Test negative destination register address.
  if (gpr.lb(-1, 1, 1) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_gpr_lb() failed. The failing subtest is \"Test negative destination register address\"." << std::endl;
    return FAIL;
  }

  // Test positive source register address outside range (>31).
  if (gpr.lb(1, 1, 32) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_gpr_lb() failed. The failing subtest is \"Test positive source register address (>31)\"." << std::endl;
    return FAIL;
  }

  // Test positive destination register address outside range (>31).
  if (gpr.lb(32, 1, 1) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_gpr_lb() failed. The failing subtest is \"Test positive destination register address (>31)\"." << std::endl;
    return FAIL;
  }

  // Test negative offset outside range (<-32,768).
  if (gpr.lb(1, MIN_IMMEDIATE-1, 2) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_gpr_lb() failed. The failing subtest is \"Test negative immediate value outside range (<-32,768)\"." << std::endl;
    return FAIL;
  }

  // Test positive offset outside range (>32,767).
  if (gpr.lb(1, MAX_IMMEDIATE+1, 2) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_gpr_lb() failed. The failing subtest is \"Test positive immediate value outside range (>32,767)\"." << std::endl;
    return FAIL;
  }

  // Test value of source register isn't a valid memory address (<256 or >=768).
  gpr.registry.store(2, 5);
  if (gpr.lb(1, 500, 2) != VALUE_ERROR) {
    std::cerr << COLOR_ERROR << "test_gpr_lb() failed. The failing subtest is \"Test value of source register isn't a valid memory address (<256 or >=768)\"." << std::endl;
    return FAIL;
  }

  // Test sum of offset and value of source register isn't a valid memory address (<256 or >=768).
  gpr.registry.store(2, 500);
  if (gpr.lb(1, 500, 2) != VALUE_ERROR) {
    std::cerr << COLOR_ERROR << "test_gpr_lb() failed. The failing subtest is \"Test sum of offset and value of source register isn't a valid memory address (<256 or >=768)\"." << std::endl;
    return FAIL;
  }

  // Test valid for success (>=256 and <768).
  gpr.registry.store(2, 5);
  if (gpr.lb(1, 500, 2) != SUCCESS) {
    std::cerr << COLOR_ERROR << "test_gpr_lb() failed. The failing subtest is \"Test valid for success (>=256 and <768)\"." << std::endl;
    return FAIL;
  }

  // All tests passed.
  std::cout << COLOR_SUCCESS << "test_gpr_lb() passed." << std::endl;
  return SUCCESS;
}

int spam::TestGPR::test_gpr_li() {
  // Test negative register address.
  if (gpr.li(-1, 1) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_gpr_li() failed. The failing subtest is \"Test negative register address\"." << std::endl;
    return FAIL;
  }

  // Test positive register address outside range (>31).
  if (gpr.li(32, 1) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_gpr_li() failed. The failing subtest is \"Test positive register address outside range (>31)\"." << std::endl;
    return FAIL;
  }

  // Test negative immediate value outside range (<-32,768).
  if (gpr.li(1, MIN_IMMEDIATE-1) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_gpr_li() failed. The failing subtest is \"Test negative immediate value outside range (<-32,768)\"." << std::endl;
    return FAIL;
  }

  // Test positive immediate value outside range (>32,767).
  if (gpr.li(1, MAX_IMMEDIATE+1) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_gpr_li() failed. The failing subtest is \"Test positive immediate value outside range (>32,767)\"." << std::endl;
    return FAIL;
  }

  // Test valid register address, immediate value fits in register for success.
  if (gpr.li(1, 10) != SUCCESS) {
    std::cerr << COLOR_ERROR << "test_gpr_li() failed. The failing subtest is \"Test valid register address, immediate value fits in register for success\"." << std::endl;
    return FAIL;
  }

  // Test valid register address, immediate value fits in register, verify register contains immediate value.
  gpr.registry.store(1, 1);
  gpr.li(1, 10);
  if (gpr.registry.load(1) != 10) {
    std::cerr << COLOR_ERROR << "test_gpr_li() failed. The failing subtest is \"Test valid register address, immediate value fits in register, verify register contains immediate value\"." << std::endl;
    return FAIL;
  }

  // All tests passed.
  std::cout << COLOR_SUCCESS << "test_gpr_li() passed." << std::endl;
  return SUCCESS;
}

int spam::TestGPR::test_gpr_subi() {
  // Test negative source address.
  if (gpr.subi(0, -1, 1) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_gpr_subi() failed. The failing subtest is \"Test negative source address\"." << std::endl;
    return FAIL;
  }

  // Test negative destination address.
  if (gpr.subi(-1, 0, 1) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_gpr_subi() failed. The failing subtest is \"Test negative destination address\"." << std::endl;
    return FAIL;
  }

  // Test positive source address outside range (>31).
  if (gpr.subi(0, 32, 1) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_gpr_subi() failed. The failing subtest is \"Test positive source address outside range (>31)\"." << std::endl;
    return FAIL;
  }

  // Test positive destination address outside range (>31).
  if (gpr.subi(32, 0, 1) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_gpr_subi() failed. The failing subtest is \"Test positive destination address outside range (>31)\"." << std::endl;
    return FAIL;
  }

  // Test negative immediate value outside range (<-32,768).
  if (gpr.subi(0, 0, MIN_IMMEDIATE-1) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_gpr_subi() failed. The failing subtest is \"Test negative immediate value outside range (<-32,768)\"." << std::endl;
    return FAIL;
  }

  // Test positive immediate value outside range (>32,767).
  if (gpr.subi(0, 0, MAX_IMMEDIATE+1) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_gpr_subi() failed. The failing subtest is \"Test negative immediate value outside range (>32,769)\"." << std::endl;
    return FAIL;
  }

  // Test difference exceeds range.
  gpr.registry.store(0, MIN_IMMEDIATE);
  if (gpr.subi(1, 0, MAX_IMMEDIATE) != VALUE_ERROR) {
    std::cerr << COLOR_ERROR << "test_gpr_subi() failed. The failing subtest is \"Test difference exceeds range\"." << std::endl;
    return FAIL;
  }

  // Test difference in range for success.
  gpr.registry.store(0, 1);
  if (gpr.subi(1, 0, 1) != SUCCESS) {
    std::cerr << COLOR_ERROR << "test_gpr_subi() failed. The failing subtest is \"Test difference in range for success\"." << std::endl;
    return FAIL;
  }

  // Test difference in range for correctness.
  gpr.registry.store(0, 3);
  gpr.subi(1, 0, 1);
  if (gpr.registry.load(1) != 2) {
    std::cerr << COLOR_ERROR << "test_gpr_subi() failed. The failing subtest is \"Test difference in range for correctness\"." << std::endl;
    return FAIL;
  }

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
