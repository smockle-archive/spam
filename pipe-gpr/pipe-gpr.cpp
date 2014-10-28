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
  id_ex_old.pc = id_ex_new.pc;
  id_ex_old.instruction = id_ex_new.instruction;

  id_ex_new.instruction = if_id_old.instruction;

  std::string instruction = id_ex_new.instruction;

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
    id_ex_new.pc = address;
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
    id_ex_new.pc = address;
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
    id_ex_new.pc = address;
  }
  else if (instruction.find("nop") != std::string::npos) {
    pc = id_ex_old.pc;
  }
  else return FAIL;

  return SUCCESS;
}

int spam::PipeGPR::access_memory() {
  
  mem_wb_old.result = mem_wb_new.result;
  mem_wb_old.instruction = mem_wb_new.instruction;

  mem_wb_new.instruction = ex_mem_old.instruction;

  std::string instruction = mem_wb_new.instruction;

  if(instruction.find("la") != std::string::npos
  || instruction.find("lb") != std::string::npos
  || instruction.find("li") != std::string::npos) {
    // LA rd, lb
    // load value at label's address
    //
    // LB rd, rs, of
    // load byte at address stored in rs, plus the offset of
    //
    // LI rd, im
    // load immediate
    if(instruction.find("la") != std::string::npos) {
      std::string label = instruction.substr(instruction.find(", ") + 2);
      int address = atoi(label.c_str());
      int result = atoi(memory.read(address));
      mem_wb_new.result = result;
    }
    else if(instruction.find("lb") != std::string::npos) {
      std::string grepper = instruction.substr(instruction.find(", ") + 2);
      int reg = atoi(grepper.substr(0, grepper.find(",")).c_str());
      reg = registry.load(reg);

      grepper = grepper.substr(grepper.find(", ") + 2);
      int offset = atoi(grepper.c_str());

      int result = atoi(memory.read(reg + offset));
      mem_wb_new.result = result;
    }
    else if(instruction.find("li") != std::string::npos) {
      std::string imm_str = instruction.substr(instruction.find(", ") + 2);
      int imm = atoi(imm_str.c_str());
      mem_wb_new.result = imm;
    }
  }
  
  else if(instruction.find("add") != std::string::npos
       || instruction.find("addi") != std::string::npos
       || instruction.find("subi") != std::string::npos) {
    mem_wb_new.result = ex_mem_new.result;
  }

  return SUCCESS;
}

int spam::PipeGPR::cache() {

  std::string instruction = mem_wb_old.instruction;

  if(instruction.find("add") != std::string::npos
  || instruction.find("addi") != std::string::npos
  || instruction.find("subi") != std::string::npos
  || instruction.find("la") != std::string::npos
  || instruction.find("lb") != std::string::npos
  || instruction.find("li") != std::string::npos) {

    instruction = instruction.substr(instruction.find(' ') + 1);
    int reg = atoi(instruction.substr(instruction.find(", ")).c_str());
    registry.store(reg, mem_wb_new.result);

  }

  return SUCCESS;
}

int main(int argc, char** argv) {
  
}
