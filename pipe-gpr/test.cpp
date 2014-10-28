#include "test.hpp"

// Pipeline stage methods
int spam::TestPipeGPR::test_fetch() {
  PipeGPR p;

  char* instruction = (char*)"fetchable";

  p.memory.store(T_BASE_ADDR, instruction);
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
  if(p.pc != 0) {
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
  if(p.pc != 0) {
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
  if(p.pc != 100) {
    std::cerr << COLOR_ERROR << "Decode failed to set the program counter to the proper value." << std::endl;
    std::cerr << "\t" << "Expected: 100, received: " << p.pc << std::endl;
    return FAIL;
  }

  std::cout << COLOR_SUCCESS << "Decode test passed." << std::endl;

  return SUCCESS;
}
int spam::TestPipeGPR::test_execute() {
  std::cerr << COLOR_WARNING << "Execute test is unwritten." << std::endl;

  // Basically needs to test the original GPR run() code.

  return UNWRITTEN;
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
  p.ex_mem_new.result = 300;
  p.access_memory();

  if(p.mem_wb_new.result != 300) {
    std::cerr << COLOR_ERROR << "Memory access failed to pass on the result of ex_mem to mem_wb." << std::endl;
    return FAIL;
  }

  std::cout << COLOR_SUCCESS << "Memory access test passed." << std::endl;
  std::cout << "\t" << COLOR_WARNING << "Store (syscall) subtest yet unwritten." << std::endl;
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

// Instruction methods
int spam::TestPipeGPR::test_addi() {
  std::cerr << COLOR_WARNING << "ADDI test is unwritten." << std::endl;
  return UNWRITTEN;
}
// etc.

//
//
// MAIN
//
//
int main(int argc, char** argv) {
  spam::TestPipeGPR tp;
  
  int tests_run = 5;
  int tests_passed = tests_run;

  // Tests
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
