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

    if(sold.isFUBusy()) {
      return FAIL;
    }
    if(sold.isWAW()) {
      return FAIL;
    }

    s.issue();
    return SUCCESS;

  }
  int Microboard::read_operands() {

    if(sold.isRegisterBusy()) {
      return FAIL;
    }
    if(sold.isRAW()) {
      return FAIL;
    }

    s.read_operands();
    return SUCCESS;
  }
}
