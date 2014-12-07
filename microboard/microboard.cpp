#include "microboard.hpp"

namespace spam {
  Microboard::Microboard() {
    // do nothing
  }
  Microboard::Microboard(Memory m, Registry r) {
    memory = m;
    registry = r;
  }

  // fetch next instruction from memory
  int Microboard::fetch() {
    bool pushed = (s.push(memory.readInstruction(pc)) != FAIL);
    if(strcmp((char*)s.peek().c_str(), memory.readInstruction(pc)) != 0)
      return FAIL;
    return SUCCESS;
  }

  // decode instruction & check for structural hazards
  int Microboard::issue() {

    int fuid = -1;
    std::string instr = sold.ipeek();
    std::string op = instr.substr(0, instr.find(' '));

    if(op.compare("add") == 0
    || op.compare("sub") == 0
    || op.compare("addi") == 0
    || op.compare("subi") == 0
    || op.compare("mult") == 0
    || op.compare("multi") == 0
    || op.compare("div") == 0
    || op.compare("divi") == 0) {
      fuid = INT_FU;
    }

    if(op.compare("fadd") == 0
    || op.compare("fsub") == 0) {
      fuid = FP_ADD;
    }

    if(op.compare("fmul") == 0) {
      fuid = FP_MUL;
    }

    if(op.compare("li") == 0
    || op.compare("la") == 0
    || op.compare("lb") == 0) {
      fuid = FP_MEM;
    }

    if(sold.isBusy(fuid)) {
      return FAIL;
    }
    if(sold.isWAW()) {
      return FAIL;
    }

    s.issue(instr);
    return SUCCESS;

  }
}
