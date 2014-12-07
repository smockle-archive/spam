#include "scoreboard.hpp"

namespace spam {
  int * Scoreboard::extract_source_operands(int ops[2]) {
    std::string instruction = ropeek();
    std::string op = instruction.substr(0, instruction.find(' '));

    std::string rs_str;
    std::string rt_str;

    int rs = -1;
    int rt = -1;

    // if Rsrc1 is op 1
    if(op.compare("beqz") == 0
      || op.compare("bge") == 0
      || op.compare("bne") == 0) {
        rs_str = instruction.substr(instruction.find(' ') + 1);
        rs_str = rs_str.substr(0, rs_str.find(' ') - 1);

        rs = atoi((char*)rs_str.c_str());
      }

    // if Rsrc1 is op 2
    else if(op.compare("add") == 0
      || op.compare("addi") == 0
      || op.compare("subi") == 0
      || op.compare("fadd") == 0
      || op.compare("fmul") == 0
      || op.compare("fsub") == 0) {

        rs_str = instruction.substr(instruction.find(' ') + 1);
        rs_str = rs_str.substr(rs_str.find(' ') + 1);
        rs_str = rs_str.substr(0, rs_str.find(' ') - 1);

        rs = atoi((char*)rs_str.c_str());
      }

    // if Rsrc1 is op 3
    else if(op.compare("ld") == 0
      || op.compare("sd") == 0) {
        rs_str = instruction.substr(instruction.find(' ') + 1);
        rs_str = rs_str.substr(rs_str.find(' ') + 1);
        rs_str = rs_str.substr(rs_str.find(' ') + 1);

        rs = atoi((char*)rs_str.c_str());
      }

    // if Rsrc2 is op 2
    if(op.compare("bge") == 0
      || op.compare("bne") == 0) {
        rt_str = instruction.substr(instruction.find(' ') + 1);
        rt_str = rt_str.substr(rt_str.find(' ') + 1);
        rt_str = rt_str.substr(0, rt_str.find(' ') - 1);

        rt = atoi((char*)rt_str.c_str());
      }

    // if Rsrc2 is op 3
    else if (op.compare("add") == 0
      || op.compare("fadd") == 0
      || op.compare("fmul") == 0
      || op.compare("fsub") == 0) {

        rt_str = instruction.substr(instruction.find(' ') + 1);
        rt_str = rt_str.substr(rt_str.find(' ') + 1);
        rt_str = rt_str.substr(rt_str.find(' ') + 1);

        rt = atoi((char*)rt_str.c_str());
    }

    ops[0] = rs;
    ops[1] = rt;
    return ops;
  }
  int Scoreboard::getFUID() {
    std::string instr = ipeek();
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
    return fuid;
  }
  bool Scoreboard::isFUBusy() {
    return busy[getFUID()];
  }
  bool Scoreboard::isWAW() {
    std::string instruction = ipeek();

    if(instruction.find(' ') == std::string::npos) return false; // e.g. syscall, end, nop can't cause WAW

    int rd = atoi((char*)instruction.substr(instruction.find(' ')).substr(0, instruction.find(' ')).c_str());
    for(int x = 0; x < MAX_INSTRUCTION_COUNT; x++) {

      if( (head + x > tail && head <= tail)
      ||  (head + x > tail + MAX_INSTRUCTION_COUNT && head >= tail) ) break; // if we hit an empty instruction

      int index = (head + x) % MAX_INSTRUCTION_COUNT;

      if(index == thorax) continue; // so we don't compare to the instruction in question

      if(instructions[index].second == EMPTY) break;

      int rdt = atoi((char*)instructions[index].first.substr(instructions[index].first.find(' ')).substr(0, instructions[index].first.find(' ')).c_str());

      if(rd == rdt) {
        return true;
      }
    }
    return false;
  }
  bool Scoreboard::isRAW() {

    std::string instr = ropeek();

    if(instr.find(' ') == std::string::npos) return false; // e.g. syscall, end, nop can't cause RAW

    std::string op = instr.substr(0, instr.find(' '));

    // if our operation has source registers, then
    // we need to loop through other instructions and
    // discover conflicts.
    // otherwise, RAW can't happen, so go ahead and
    // report the A-OK.
    if(
      op.compare("add") == 0
   || op.compare("addi") == 0
   || op.compare("beqz") == 0
   || op.compare("bge") == 0
   || op.compare("bne") == 0
   || op.compare("lb") == 0
   || op.compare("subi") == 0
   || op.compare("fadd") == 0
   || op.compare("fmul") == 0
   || op.compare("fsub") == 0
   || op.compare("ld") == 0
   || op.compare("sd") == 0
      ) {

        int source_ops[2] = { -1 };
        extract_source_operands(source_ops);

        for(int x = 0; x < MAX_INSTRUCTION_COUNT; x++) {
          if( (head + x > tail && head <= tail)
          ||  (head + x > tail + MAX_INSTRUCTION_COUNT && head >= tail) ) break; // if we hit an empty instruction

          int index = (head + x) % MAX_INSTRUCTION_COUNT;

          if(index == abdomen) continue; // so we don't compare to the instruction in question

          // if we haven't issued this instruction yet,
          // or we have, but it was issued after the instruction
          // at abdomen, then there is no issue
          if(instructions[index].second < ISSUE || (instructions[index].second == ISSUE && ((index < abdomen && index >= head) || (index > abdomen && index >= head)))) {
            continue;
          }

          std::string rd_str = instructions[index].first.substr(instructions[index].first.find(' '));
          rd_str = rd_str.substr(0, rd_str.find(' ') - 1);

          int rd = atoi((char*)rd_str.c_str());

          if(rd == source_ops[0] || rd == source_ops[1]) return true;
        }
    }
    return false;
  }
  bool Scoreboard::isRegisterBusy() {
    return false;
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
    else if (tail == EMPTY) tail = head;
    else tail++;

    instructions[tail] = std::make_pair(instruction, ISSUE);

    return SUCCESS;
  }
  std::string Scoreboard::pop() {
    if(isEmpty()) {
      return "";
    }
    std::string instruction = instructions[head].first;
    instructions[head].first = "";
    instructions[head].second = EMPTY;

    if(head == tail) tail = EMPTY; // we just popped the last element, so we're empty
    else if(head == MAX_INSTRUCTION_COUNT) head = 0;
    else head++;

    return instruction;
  }
  std::string Scoreboard::peek() {
    if(isEmpty()) {
      return "";
    }
    return instructions[head].first;
  }
  int Scoreboard::issue() {

    int fuid = getFUID();

    if(fuid == -1) {
      std::cerr << COLOR_ERROR << "Invalid command (" << ipeek() << ")." << std::endl;
      return FAIL;
    }

    busy[fuid] = true;
    instructions[thorax].second = READ_OPS;
    // TODO: other data updates
    if(thorax == 3) thorax = 0;
    else thorax++;

    return SUCCESS;
  }
  int Scoreboard::read_operands() {
    std::string instr = ropeek();

    instructions[abdomen].second = EXE_COMPLETE;
    // TODO: other data updates
    if(abdomen == 3) abdomen = 0;
    else abdomen++;

    return SUCCESS;
  }

  std::string Scoreboard::ipeek() {
    if(isEmpty()) {
      return "";
    }
    return instructions[thorax].first;
  }

  std::string Scoreboard::ropeek() {
    if(isEmpty()) {
      return "";
    }
    return instructions[abdomen].first;
  }
}
