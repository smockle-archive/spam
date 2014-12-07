#include "test.hpp"
namespace spam {
  TestMicroboard::TestMicroboard () {
    // do nothing
  }

  int TestMicroboard::test_fetch() {

    Memory m;
    Registry r;

    Microboard mb (m, r);

    // Ensure we can fetch an instruction from memory.
    mb.pc = T_BASE_ADDR;
    std::string instr = "la 0, nop";
    mb.memory.store(T_BASE_ADDR, (char*)instr.c_str());
    mb.fetch();
    if(strcmp((char *)mb.s.peek().c_str(), (char*)instr.c_str()) != 0) {
      std::cerr << COLOR_ERROR << "Fetched wrong instruction from memory. (Expected \"" << instr << "\", got \"" << mb.s.peek() << "\".)" << std::endl;
      return FAIL;
    }

    // All tests passed.
    std::cout << COLOR_SUCCESS << "Fetch test passed." << std::endl;
    return SUCCESS;
  }

  int TestMicroboard::test_issue() {

    // Ensure if functional unit is available and no WAW would occur, we issue.
    Memory m;
    Registry r;
    Microboard mb (m, r);

    mb.pc = T_BASE_ADDR;
    mb.memory.store(mb.pc, (char*)"li 0, 30");
    mb.memory.store(mb.pc + 1, (char*)"li 1, 20");

    mb.fetch();
    mb.sold = mb.s;
    mb.pc++;
    mb.fetch();
    mb.issue();

    // Assumedly, FP_MEM will handle load operations, so we need to count
    // it as busy if it's been issued the above command.
    if(!mb.s.isFUBusy()) {
      std::cerr << COLOR_ERROR << "Didn't properly mark FP_MEM as busy when it was previously not busy and issued an LI instruction." << std::endl;
      return FAIL;
    }

    // Ensure if functional unit is busy for the current command type, we delay.
    mb.sold = mb.s;
    if(mb.issue() != FAIL) {
      std::cerr << COLOR_ERROR << "Didn't delay when functional unit FP_MEM was busy and an LI instruction was issued." << std::endl;
      return FAIL;
    }

    // Ensure if WAW would occur, we delay.
    // (WAW: write after write. WAW occurs when our current
    // destination is the same as a destination register of
    // another active instruction.)
    mb.pc--;
    mb.fetch();
    mb.sold = mb.s;
    mb.sold.thorax--;
    mb.sold.busy[FP_MEM] = false;
    if(mb.issue() != FAIL) {
      std::cerr << COLOR_ERROR << "Didn't delay when WAW would occur." << std::endl;
      return FAIL;
    }

    // All tests passed.
    std::cout << COLOR_SUCCESS << "Issue test passed." << std::endl;
    return SUCCESS;
  }

  int TestMicroboard::test_read_operands() {

    // Source registers aren't available if an
    // earlier-issued active instruction is
    // going to write to that register.

    // Source registers also aren't available
    // if a currently-active functional unit is
    // writing to that register.

    // Ensure if everything is peachy-keen,
    // we progress.

    Memory m;
    Registry r;
    Microboard mb(m, r);

    mb.pc = T_BASE_ADDR;
    mb.memory.store(mb.pc, (char *)"li 0, 30");
    mb.memory.store(mb.pc + 1, (char *)"la 1, 2");
    mb.memory.store(mb.pc + 2, (char *)"add 3, 1, 2");

    mb.fetch();
    mb.sold = mb.s;
    mb.pc++;
    mb.fetch();
    mb.issue();
    mb.sold = mb.s;
    mb.pc++;
    mb.fetch();
    mb.issue();
    mb.sold = mb.s;

    if(mb.read_operands() != SUCCESS) {
      std::cerr << COLOR_ERROR << "Failed to read operands when it should've been able to." << std::endl;
    }

    mb.sold = mb.s;
    mb.read_operands();
    mb.sold = mb.s;

    if(mb.read_operands() != FAIL) {
      std::cerr << COLOR_ERROR << "Read operands that it shouldn't have due to failing to detect a RAW hazard." << std::endl;
      return FAIL;
    }

    // Ensure if source registers aren't available
    // due to earlier-issued active instructions,
    // we delay.

    std::cout << COLOR_SUCCESS << "Read operands test passed." << std::endl;
    return SUCCESS;
  }
  int TestMicroboard::test_execute() {
    std::cerr << COLOR_WARNING << "Execute test is unwritten." << std::endl;
    return UNWRITTEN;
  }
  int TestMicroboard::test_write() {
    std::cerr << COLOR_WARNING << "Write test is unwritten." << std::endl;
    return UNWRITTEN;
  }
}

int main(int argc, char** argv) {
  spam::TestMicroboard tmb;

  int tests_run = 5;
  int tests_passed = 5;

  tests_passed += tmb.test_fetch();
  tests_passed += tmb.test_issue();
  tests_passed += tmb.test_read_operands();
  tests_passed += tmb.test_execute();
  tests_passed += tmb.test_write();

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
