#include "scoreboard.hpp"

namespace spam {

  bool Scoreboard::isBusy(int fuid) {
    return busy[fuid];
  }
  bool Scoreboard::isWAW() {
    std::string instruction = peek();

  }
  bool Scoreboard::isFull() {
    return tail != -1 //if tail = -1, then we're empty, so we're certainly not full
        && ((tail - head) == MAX_INSTRUCTION_COUNT
        || (tail - head) == -1);
  }
  bool Scoreboard::isEmpty() {
    return tail == -1;
  }
  int Scoreboard::push(std::string instruction) {
    if(isFull()) {
      return FAIL;
    }

    if(tail == MAX_INSTRUCTION_COUNT) tail = 0;
    else tail++;

    instructions[tail] = instruction;

    return SUCCESS;
  }
  std::string Scoreboard::pop() {
    if(isEmpty()) {
      return "";
    }
    std::string instruction = instructions[head];
    instructions[head] = "";

    if(head == tail) tail = -1; // we just popped the last element, so we're empty

    if(head == MAX_INSTRUCTION_COUNT) head = 0;
    else head++;

    return instruction;
  }
  std::string Scoreboard::peek() {
    if(isEmpty()) {
      return "";
    }
    return instructions[head];
  }
  int Scoreboard::issue(std::string instr) {

    std::string op = instr.substr(0, instr.find(' '));
    int fuid = -1;

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

    if(fuid == -1) {
      std::cerr << COLOR_ERROR << "Invalid command (" << op << ")." << std::endl;
      return FAIL;
    }

    busy[fuid] = true;
    // TODO: other data updates
    if(thorax == 3) thorax = 0;
    else thorax++;

    return SUCCESS;
  }
  std::string Scoreboard::ipeek() {
    if(isEmpty()) {
      return "";
    }
    return instructions[thorax];
  }

}
