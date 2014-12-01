#include "test.hpp"

int spam::TestPipeGPR::test_add() {
  // Test negative source1 address.
  if (p.add(-1, 1) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_add() failed. The failing subtest is \"Test negative source1 address\"." << std::endl;
    return FAIL;
  }

  // Test negative source2 address.
  if (p.add(1, -1) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_add() failed. The failing subtest is \"Test negative source2 address\"." << std::endl;
    return FAIL;
  }

  // Test positive source1 address outside range (>31).
  if (p.add(32, 1) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_add() failed. The failing subtest is \"Test positive source1 address outside range (>31)\"." << std::endl;
    return FAIL;
  }

  // Test positive source2 address outside range (>31).
  if (p.add(1, 32) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_add() failed. The failing subtest is \"Test positive source2 address outside range (>31)\"." << std::endl;
    return FAIL;
  }

  // Test sum exceeds range.
  p.registry.store(0, MAX_IMMEDIATE-1);
  p.registry.store(1, MAX_IMMEDIATE-1);
  if (p.add(0, 1) != VALUE_ERROR) {
    std::cerr << COLOR_ERROR << "test_add() failed. The failing subtest is \"Test sum exceeds range\"." << std::endl;
    return FAIL;
  }

  // Test sum in range for success.
  p.registry.store(0, 1);
  p.registry.store(1, 1);
  if (p.add(0, 1) != SUCCESS) {
    std::cerr << COLOR_ERROR << "test_add() failed. The failing subtest is \"Test sum in range for success\"." << std::endl;
    return FAIL;
  }

  // Test sum in range for correctness.
  p.registry.store(0, 1);
  p.registry.store(1, 1);
  p.add(0, 1);
  if (p.ex_mem_new.result != 2) {
    std::cerr << COLOR_ERROR << "test_add() failed. The failing subtest is \"Test sum in range for correctness\"." << std::endl;
    return FAIL;
  }

  // All tests passed.
  std::cout << COLOR_SUCCESS << "test_add() passed." << std::endl;
  return SUCCESS;
}

int spam::TestPipeGPR::test_addi() {
  // Test negative source address.
  if (p.addi(-1, 1) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_addi() failed. The failing subtest is \"Test negative source address\"." << std::endl;
    return FAIL;
  }

  // Test positive source address outside range (>31).
  if (p.addi(32, 1) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_addi() failed. The failing subtest is \"Test positive source address outside range (>31)\"." << std::endl;
    return FAIL;
  }

  // Test negative immediate value outside range (<-32,768).
  if (p.addi(0, MIN_IMMEDIATE-1) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_addi() failed. The failing subtest is \"Test negative immediate value outside range (<-32,768)\"." << std::endl;
    return FAIL;
  }

  // Test positive immediate value outside range (>32,767).
  if (p.addi(0, MAX_IMMEDIATE+1) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_addi() failed. The failing subtest is \"Test negative immediate value outside range (>32,769)\"." << std::endl;
    return FAIL;
  }

  // Test sum exceeds range.
  p.registry.store(0, MAX_IMMEDIATE-1);
  if (p.addi(0, MAX_IMMEDIATE-1) != VALUE_ERROR) {
    std::cerr << COLOR_ERROR << "test_addi() failed. The failing subtest is \"Test sum exceeds range\"." << std::endl;
    return FAIL;
  }

  // Test sum in range for success.
  p.registry.store(0, 1);
  if (p.addi(0, 1) != SUCCESS) {
    std::cerr << COLOR_ERROR << "test_addi() failed. The failing subtest is \"Test sum in range for success\"." << std::endl;
    return FAIL;
  }

  // Test sum in range for correctness.
  p.registry.store(0, 1);
  p.addi(0, 1);
  if (p.ex_mem_new.result != 2) {
    std::cerr << COLOR_ERROR << "test_addi() failed. The failing subtest is \"Test sum in range for correctness\"." << std::endl;
    return FAIL;
  }

  // All tests passed.
  std::cout << COLOR_SUCCESS << "test_addi() passed." << std::endl;
  return SUCCESS;
}

int spam::TestPipeGPR::test_la() {
  // Test negative variable address.
  if (p.la(-1) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_la() failed. The failing subtest is \"Test negative variable address\"." << std::endl;
    return FAIL;
  }

  // Test positive variable address outside range (<256 or >=512).
  if (p.la(1) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_la() failed. The failing subtest is \"Test positive variable address outside range (<256 or >=512)\"." << std::endl;
    return FAIL;
  }

  // Test valid variable address for success.
  if (p.la(D_BASE_ADDR) != SUCCESS) {
    std::cerr << COLOR_ERROR << "test_la() failed. The failing subtest is \"Test valid variable address for success\"." << std::endl;
    return FAIL;
  }

  // Test valid variable address, verify register contains value of variable.
  p.registry.store(1, 1);
  p.memory.store(D_BASE_ADDR, (char *) "10");
  p.la(D_BASE_ADDR);
  if (*p.memory.read(p.ex_mem_new.result) != '1'
   && *p.memory.read(p.ex_mem_new.result + 1) != '0') {
    std::cerr << COLOR_ERROR << "test_la() failed. The failing subtest is \"Test valid variable address, verify register contains value of variable\"." << std::endl;
    return FAIL;
  }

  // All tests passed.
  std::cout << COLOR_SUCCESS << "test_la() passed." << std::endl;
  return SUCCESS;
}

int spam::TestPipeGPR::test_lb() {
  // Test negative source register address.
  if (p.lb(1, -1) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_lb() failed. The failing subtest is \"Test negative source register address\"." << std::endl;
    return FAIL;
  }

  // Test positive source register address outside range (>31).
  if (p.lb(1, 32) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_lb() failed. The failing subtest is \"Test positive source register address (>31)\"." << std::endl;
    return FAIL;
  }

  // Test negative offset outside range (<-32,768).
  if (p.lb(MIN_IMMEDIATE-1, 2) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_lb() failed. The failing subtest is \"Test negative immediate value outside range (<-32,768)\"." << std::endl;
    return FAIL;
  }

  // Test positive offset outside range (>32,767).
  if (p.lb(MAX_IMMEDIATE+1, 2) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_lb() failed. The failing subtest is \"Test positive immediate value outside range (>32,767)\"." << std::endl;
    return FAIL;
  }

  // Test sum of offset and value of source register isn't a valid memory address (<256 or >=768).
  p.registry.store(2, 500);
  if (p.lb(500, 2) != VALUE_ERROR) {
    std::cerr << COLOR_ERROR << "test_lb() failed. The failing subtest is \"Test sum of offset and value of source register isn't a valid memory address (<256 or >=768)\"." << std::endl;
    return FAIL;
  }

  // Test valid memory address for success.
  p.registry.store(2, 500);
  if (p.lb(5, 2) != SUCCESS) {
    std::cerr << COLOR_ERROR << "test_lb() failed. The failing subtest is \"Test valid memory address for success\"." << std::endl;
    return FAIL;
  }

  // Test valid memory address, verify register contains value at address.
  p.memory.store(505, (char *) "10");
  p.registry.store(2, 500);
  p.lb(5, 2);
  if (p.ex_mem_new.result != *p.memory.read(505)) {
    std::cerr << COLOR_ERROR << "test_lb() failed. The failing subtest is \"Test valid memory address, verify register contains value at address\"." << std::endl;
    return FAIL;
  }

  // All tests passed.
  std::cout << COLOR_SUCCESS << "test_lb() passed." << std::endl;
  return SUCCESS;
}

int spam::TestPipeGPR::test_li() {
  // Test negative immediate value outside range (<-32,768).
  if (p.li(MIN_IMMEDIATE-1) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_li() failed. The failing subtest is \"Test negative immediate value outside range (<-32,768)\"." << std::endl;
    return FAIL;
  }

  // Test positive immediate value outside range (>32,767).
  if (p.li(MAX_IMMEDIATE+1) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_li() failed. The failing subtest is \"Test positive immediate value outside range (>32,767)\"." << std::endl;
    return FAIL;
  }

  // Test valid register address, immediate value fits in register for success.
  if (p.li(10) != SUCCESS) {
    std::cerr << COLOR_ERROR << "test_li() failed. The failing subtest is \"Test valid register address, immediate value fits in register for success\"." << std::endl;
    return FAIL;
  }

  // Test valid register address, immediate value fits in register, verify register contains immediate value.
  p.ex_mem_new.result = 1;
  p.li(10);
  if (p.ex_mem_new.result != 10) {
    std::cerr << COLOR_ERROR << "test_li() failed. The failing subtest is \"Test valid register address, immediate value fits in register, verify register contains immediate value\"." << std::endl;
    return FAIL;
  }

  // All tests passed.
  std::cout << COLOR_SUCCESS << "test_li() passed." << std::endl;
  return SUCCESS;
}

int spam::TestPipeGPR::test_subi() {
  // Test negative source address.
  if (p.subi(-1, 1) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_subi() failed. The failing subtest is \"Test negative source address\"." << std::endl;
    return FAIL;
  }

  // Test positive source address outside range (>31).
  if (p.subi(32, 1) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_subi() failed. The failing subtest is \"Test positive source address outside range (>31)\"." << std::endl;
    return FAIL;
  }

  // Test negative immediate value outside range (<-32,768).
  if (p.subi(0, MIN_IMMEDIATE-1) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_subi() failed. The failing subtest is \"Test negative immediate value outside range (<-32,768)\"." << std::endl;
    return FAIL;
  }

  // Test positive immediate value outside range (>32,767).
  if (p.subi(0, MAX_IMMEDIATE+1) != ARGUMENT_ERROR) {
    std::cerr << COLOR_ERROR << "test_subi() failed. The failing subtest is \"Test negative immediate value outside range (>32,769)\"." << std::endl;
    return FAIL;
  }

  // Test difference exceeds range.
  p.registry.store(0, MIN_IMMEDIATE);
  if (p.subi(0, MAX_IMMEDIATE) != VALUE_ERROR) {
    std::cerr << COLOR_ERROR << "test_subi() failed. The failing subtest is \"Test difference exceeds range\"." << std::endl;
    return FAIL;
  }

  // Test difference in range for success.
  p.registry.store(0, 1);
  if (p.subi(0, 1) != SUCCESS) {
    std::cerr << COLOR_ERROR << "test_subi() failed. The failing subtest is \"Test difference in range for success\"." << std::endl;
    return FAIL;
  }

  // Test difference in range for correctness.
  p.registry.store(0, 3);
  p.subi(0, 1);
  if (p.ex_mem_new.result != 2) {
    std::cerr << COLOR_ERROR << "test_subi() failed. The failing subtest is \"Test difference in range for correctness\"." << std::endl;
    return FAIL;
  }

  // All tests passed.
  std::cout << COLOR_SUCCESS << "test_subi() passed." << std::endl;
  return SUCCESS;
}

int spam::TestPipeGPR::test_syscall() {
  // Test reading console input. ($V0 contains 8)
  p.registry.store(V0_ADDR, SYSCALL_CIN);
  if (p.syscall() != SYSCALL_CIN) {
    std::cerr << COLOR_ERROR << "test_syscall() failed. The failing subtest is \"Test reading console input\"." << std::endl;
    return FAIL;
  }

  // Test writing console output. ($V0 contains 4)
  p.registry.store(V0_ADDR, SYSCALL_COUT);
  if (p.syscall() != SYSCALL_COUT) {
    std::cerr << COLOR_ERROR << "test_syscall() failed. The failing subtest is \"Test writing console output\"." << std::endl;
    return FAIL;
  }

  // Test program termination. ($V0 contains 10)
  p.registry.store(V0_ADDR, SYSCALL_END);
  if (p.syscall() != SYSCALL_END) {
    std::cerr << COLOR_ERROR << "test_syscall() failed. The failing subtest is \"Test program termination\"." << std::endl;
    return FAIL;
  }

  // All tests passed.
  std::cout << COLOR_SUCCESS << "test_syscall() passed." << std::endl;
  return SUCCESS;
}

int spam::TestPipeGPR::test_nop() {
  // Verify returns true.
  if (p.nop() != SUCCESS) {
    std::cerr << COLOR_ERROR << "test_nop() failed. The failing subtest is \"Verify returns true\"." << std::endl;
    return FAIL;
  }

  // All tests passed.
  std::cout << COLOR_SUCCESS << "test_nop() passed." << std::endl;
  return SUCCESS;
}

int spam::TestPipeGPR::test_end() {
  // Verify returns true.
  if (p.end() != SUCCESS) {
    std::cerr << COLOR_ERROR << "test_end() failed. The failing subtest is \"Verify returns true\"." << std::endl;
    return FAIL;
  }

  // All tests passed.
  std::cout << COLOR_SUCCESS << "test_end() passed." << std::endl;
  return SUCCESS;
}

// Pipeline stage methods
int spam::TestPipeGPR::test_fetch() {
  PipeGPR p;

  char* instruction = (char*)"fetchable";

  p.pc = T_BASE_ADDR;
  p.memory.store(p.pc, instruction);
  p.fetch();

  std::string ins_str = instruction;
  std::string if_id_str = p.if_id_new.instruction;

  if(if_id_str != ins_str) {
    std::cerr << COLOR_ERROR << "Fetch failed. Instruction expected: " << instruction << ", fetched: " << p.if_id_new.instruction << std::endl;
    return FAIL;
  }

  std::cout << COLOR_SUCCESS << "Fetch test passed." << std::endl;
  return SUCCESS;
}
int spam::TestPipeGPR::test_decode() {
  PipeGPR p;

  // Ensure we properly decode an instruction that doesn't read from the registers
  p.if_id_old.instruction = (char*)"syscall";
  p.decode();

  if(p.id_ex_new.rs != -1
  || p.id_ex_new.rt != -1) {
    std::cerr << COLOR_ERROR << "Decode didn't properly default register values." << std::endl;
    std::cerr << "\t" << "Expected: (-1, -1), received: (" << p.id_ex_new.rs << ", " << p.id_ex_new.rt << ")" << std::endl;
    return FAIL;
  }
  if(p.pc != 0) {
    std::cerr << COLOR_ERROR << "Decode updated the program counter when it should not have. (registerless instruction)" << std::endl;
    std::cerr << "\t" << "Expected: 0, received: " << p.pc << std::endl;
    return FAIL;
  }

  // Ensure we properly decode a 1-register-read instruction
  int rs = 10;
  p.registry.store(1, rs);
  p.if_id_old.instruction = (char*)"addi 0, 1, 2";
  p.decode();

  if(p.id_ex_new.rs != rs
  || p.id_ex_new.rt != -1) {
    std::cerr << COLOR_ERROR << "Decode failed to grab the proper register values." << std::endl;
    std::cerr << "\t" << "Expected: (" << rs << ", -1), ";
    std::cerr << "received: (" << p.id_ex_new.rs << ", " << p.id_ex_new.rt << ")" << std::endl;
    return FAIL;
  }
  if(p.id_ex_new.pc != 0) {
    std::cerr << COLOR_ERROR << "Decode updated the program counter when it should not have. (1-register instruction)" << std::endl;
    std::cerr << "\t" << "Expected: 0, received: " << p.pc << std::endl;
  }


  // Ensure we properly decode a 2-register-read instruction
  // recall that int rs = 10
      rs = 11;
  int rt = 21;
  p.registry.store(1, rs);
  p.registry.store(2, rt);
  p.if_id_old.instruction = (char*)"add 0, 1, 2";
  p.decode();

  if(p.id_ex_new.rs != rs
  || p.id_ex_new.rt != rt) {
    std::cerr << COLOR_ERROR << "Decode failed to grab the proper register addresses." << std::endl;
    std::cerr << "\t" << "Expected: (" << rs << ", " << rt << "), ";
    std::cerr << "received: (" << p.id_ex_new.rs << ", " << p.id_ex_new.rt << ")" << std::endl;
    return FAIL;
  }
  if(p.id_ex_new.pc != 0) {
    std::cerr << COLOR_ERROR << "Decode updated the program counter when it should not have. (2-register instruction)" << std::endl;
    std::cerr << "\t" << "Expected: 0, received: " << p.pc << std::endl;
    return FAIL;
  }

  // Ensure we properly handle branching instructions
  rs = 33;
  rt = 34;
  p.registry.store(1, rs);
  p.registry.store(2, rt);
  p.if_id_old.instruction = (char*)"bge 1, 2, 100";
  p.decode();

  if(p.id_ex_new.rs != rs
  || p.id_ex_new.rt != rt) {
    std::cerr << COLOR_ERROR << "Decode failed to grab the proper register values." << std::endl;
    std::cerr << "\t" << "Expected: (" << rs << ", " << rt << "), ";
    std::cerr << "received: (" << p.id_ex_new.rs << ", " << p.id_ex_new.rt << ")" << std::endl;
    return FAIL;
  }
  if(p.id_ex_new.pc != 100) {
    std::cerr << COLOR_ERROR << "Decode failed to set the program counter to the proper value." << std::endl;
    std::cerr << "\t" << "Expected: 100, received: " << p.pc << std::endl;
    return FAIL;
  }

  std::cout << COLOR_SUCCESS << "Decode test passed." << std::endl;

  return SUCCESS;
}

int spam::TestPipeGPR::test_execute() {
  //TODO: fill this in if we deem it important
  std::cout << COLOR_SUCCESS << "Execute test passed." << std::endl;
  return SUCCESS;
}

int spam::TestPipeGPR::test_access_memory() {

  PipeGPR p;

  // Ensure we don't update the mem_wb_new latch
  // if the instruction isn't a memory access.
  p.ex_mem_old.instruction = (char*)"bge 1, 2, 100";
  int result = p.mem_wb_new.result;
  p.access_memory();

  if(p.mem_wb_new.result != result) {
    std::cerr << COLOR_ERROR << "Memory access inappropriately edited the mem_wb latch." << std::endl;
    return FAIL;
  }

  // Ensure we do update the mem_wb_new latch
  // if the instruction is a load instruction.
  p.ex_mem_old.instruction = (char*)"li 1, 200";
  p.registry.store(1, 100);
  p.access_memory();

  if(p.mem_wb_new.result != 200) {
    std::cerr << COLOR_ERROR << "Memory access failed to set the proper value in the mem_wb latch." << std::endl;
    return FAIL;
  }

  // Ensure we pass the ex_mem result on to
  // the mem_wb latch for R-type instructions.
  p.ex_mem_old.instruction = (char*)"add 0, 1, 2";
  p.ex_mem_old.result = 300;
  p.access_memory();

  if(p.mem_wb_new.result != 300) {
    std::cerr << COLOR_ERROR << "Memory access failed to pass on the result of ex_mem to mem_wb." << std::endl;
    return FAIL;
  }

  // Ensure we can write to memory.
  char* input = (char*)"jake and clay write awesome all-day";
  p.ex_mem_old.instruction = (char*)"syscall";
  p.registry.store(A0_ADDR, T_BASE_ADDR);
  p.ex_mem_old.input = input;
  p.access_memory();

  if(std::string(p.memory.readInstruction(p.registry.load(A0_ADDR))) != std::string(input)) {
    std::cerr << COLOR_ERROR << "Memory access failed to write to memory." << std::endl;
    return FAIL;
  }

  std::cout << COLOR_SUCCESS << "Memory access test passed." << std::endl;
  return SUCCESS;
}
int spam::TestPipeGPR::test_cache() {

  PipeGPR p;

  // Ensure that R-type instructions write to cache
  // properly.
  p.mem_wb_old.instruction = (char*)"add 0, 1, 2";
  p.registry.store(0, 100);
  p.mem_wb_new.result = 400;
  p.cache();

  if(p.registry.load(0) != 400) {
    std::cerr << COLOR_ERROR << "Cache failed to store result in proper register." << std::endl;
    std::cerr << "\t" << "Expected: 400, received: " << p.registry.load(0) << std::endl;
    return FAIL;
  }

  // Ensure that load-type instructions write to
  // cache properly.
  p.mem_wb_old.instruction = (char*)"li 0, 500";
  p.registry.store(0, 100);
  p.mem_wb_new.result = 500;
  p.cache();

  if(p.registry.load(0) != 500) {
    std::cerr << COLOR_ERROR << "Cache failed to load value into proper register." << std::endl;
    std::cerr << "\t" << "Expected: 500, received: " << p.registry.load(0) << std::endl;
    return FAIL;
  }

  std::cout << COLOR_SUCCESS << "Cache test passed." << std::endl;
  return SUCCESS;
}

//
//
// MAIN
//
//
int main(int argc, char** argv) {
  spam::TestPipeGPR tp;

  int tests_run = 13;
  int tests_passed = tests_run;

  // Tests
  tests_passed += tp.test_add();
  tests_passed += tp.test_addi();
  tests_passed += tp.test_la();
  tests_passed += tp.test_lb();
  tests_passed += tp.test_li();
  tests_passed += tp.test_subi();
  tests_passed += tp.test_syscall();
  tests_passed += tp.test_nop();
  tests_passed += tp.test_end();
  tests_passed += tp.test_fetch();
  tests_passed += tp.test_decode();
  tests_passed += tp.test_execute();
  tests_passed += tp.test_access_memory();
  tests_passed += tp.test_cache();

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

  return (tests_failed == 0) ? SUCCESS : FAIL;
}
