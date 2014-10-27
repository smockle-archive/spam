#include "pipe-gpr.hpp"

int spam::PipeGPR::fetch() {
  char* instruction = memory.readInstruction(T_BASE_ADDR + pc);
  if_id_old.instruction = if_id_new.instruction;
  if_id_new.instruction = instruction;

  if(if_id_new.instruction != instruction) return VALUE_ERROR;
  return SUCCESS;
}

int spam::PipeGPR::decode() {
  
  id_ex_old.rs = id_ex_new.rs;
  id_ex_old.rt = id_ex_new.rt;  

  std::string instruction = std::string(if_id_new.instruction);

  // Instructions list:
  //
  // ADD  rd, rs, rt
  // ADDI rd, rs, im
  // B    lb
  // BEQZ rs, lb
  // BGE  rs, rt, lb
  // BNE  rs, rt, lb
  // LA   rd, lb
  // LB   rd, rs, im
  // LI   rd, im
  // NOP
  // SUBI rd, rs, im
  // SYSCALL
  //
  // We need to populate rs and rt.
  // rs first, nothing else
  //   BEQZ
  //
  // rs first, rt next
  //   BGE
  //   BNE
  //
  // rs second, nothing else
  //   ADDI
  //   LB
  //   SUBI
  //
  // rs second, rt third
  //   ADD

  if(instruction.find("beqz") != std::string::npos) {
    int address = atoi(instruction.substr(instruction.find(' ') + 1).c_str());
    id_ex_new.rs = registry.load(address);
    id_ex_new.rt = -1;

    instruction = instruction.substr(instruction.find(", ") + 2);
    address = atoi(instruction.c_str());
    pc = address;
  }
  else if(
          instruction.find("bge") != std::string::npos
       || instruction.find("bne") != std::string::npos
          ) {
    int address = atoi(instruction.substr(instruction.find(' ') + 1, instruction.find(',')).c_str());
    id_ex_new.rs = registry.load(address);

    instruction = instruction.substr(instruction.find(", ") + 2);
    address = atoi(instruction.substr(0, instruction.find(", ")).c_str());
    id_ex_new.rt = registry.load(address);

    instruction = instruction.substr(instruction.find(", ") + 2);
    address = atoi(instruction.c_str());
    pc = address;
  }
  else if (
           instruction.find("addi") != std::string::npos
        || instruction.find("subi") != std::string::npos
        || instruction.find("lb")   != std::string::npos
          ) {
    instruction = instruction.substr(instruction.find(", ") + 2);
    int address = atoi(instruction.c_str());
    id_ex_new.rs = registry.load(address);
    id_ex_new.rt = -1;
  }
  else if (instruction.find("add") != std::string::npos) {
    instruction = instruction.substr(instruction.find(", ") + 2);
    int address = atoi(instruction.substr(0, instruction.find(' ')).c_str());
    id_ex_new.rs = registry.load(address);

    instruction = instruction.substr(instruction.find(", ") + 2);
    address = atoi(instruction.c_str());
    id_ex_new.rt = registry.load(address);
  }
  else if (instruction.find("syscall") != std::string::npos) {
    // do nothing
  }
  else if (instruction.find("b ") != std::string::npos) {
    int address = atoi(instruction.substr(instruction.find(' ') + 1).c_str());
    pc = address;
  }
  else return FAIL;

  return SUCCESS;
}

int spam::PipeGPR::access_memory() {
  return UNWRITTEN;
}
