#include "pipe-gpr.hpp"
#include <string.h>

spam::PipeGPR::PipeGPR() {
};

spam::PipeGPR::PipeGPR(Registry * r, Memory * m) {
  memory = *m;
  registry = *r;
}

int spam::PipeGPR::add(int rsrc1, int rsrc2) {
  // Verify arguments.
  if (rsrc1 < 0 || rsrc1 > 31 || rsrc2 < 0 || rsrc2 > 31) {
    #ifndef TEST
    std::cout << COLOR_ERROR << "Source register address must be in the range 0 to 31." << std::endl;
    #endif
    return ARGUMENT_ERROR;
  }

  // Calculate sum.
  int sum = registry.load(rsrc1) + registry.load(rsrc2);

  // Verify sum.
  if (sum > MAX_IMMEDIATE || sum < MIN_IMMEDIATE) {
    #ifndef TEST
    std::cout << COLOR_ERROR << "Sum cannot exceed " << MAX_IMMEDIATE << "." << std::endl;
    #endif
    return VALUE_ERROR;
  }

  ex_mem_new.result = sum;
  return SUCCESS;
}

int spam::PipeGPR::addi(int rsrc, int imm) {
  // Verify arguments.
  if (rsrc < 0 || rsrc > 31) {
    #ifndef TEST
    std::cout << COLOR_ERROR << "Source register address must be in the range 0 to 31." << std::endl;
    #endif
    return ARGUMENT_ERROR;
  }

  if (imm < MIN_IMMEDIATE || imm > MAX_IMMEDIATE) {
    #ifndef TEST
    std::cout << COLOR_ERROR << "Immediate value must be in the range " << MIN_IMMEDIATE << " to " << MAX_IMMEDIATE << "." << std::endl;
    #endif
    return ARGUMENT_ERROR;
  }

  // Calculate sum.
  int sum = registry.load(rsrc) + imm;

  // Verify sum.
  if (sum > MAX_IMMEDIATE || sum < MIN_IMMEDIATE) {
    #ifndef TEST
    std::cout << COLOR_ERROR << "Sum cannot exceed " << MAX_IMMEDIATE << "." << std::endl;
    #endif
    return VALUE_ERROR;
  }

  ex_mem_new.result = sum;
  return SUCCESS;
}

int spam::PipeGPR::la(int variable_addr) {
  // Verify arguments.
  if (variable_addr < 256 || variable_addr >= 512) {
    #ifndef TEST
    std::cout << COLOR_ERROR << "Variable address must be in the range 256 to 512." << std::endl;
    #endif
    return ARGUMENT_ERROR;
  }

  std::string variable = "";
  int i = variable_addr;
  char c = *memory.read(i);

  while(c != '\0' && c != '\n') {
    variable += c;
    i++;
    c = *memory.read(i);
  }

  ex_mem_new.result = variable_addr;
  return SUCCESS;
}

int spam::PipeGPR::lb(int offset, int rsrc) {
  // Verify arguments.
  if (offset < MIN_IMMEDIATE || offset > MAX_IMMEDIATE) {
    #ifndef TEST
    std::cout << COLOR_ERROR << "Immediate value must be in the range " << MIN_IMMEDIATE << " to " << MAX_IMMEDIATE << "." << std::endl;
    #endif
    return ARGUMENT_ERROR;
  }

  if (rsrc < 0 || rsrc > 31) {
    #ifndef TEST
    std::cout << COLOR_ERROR << "Source register address must be in the range 0 to 31." << std::endl;
    #endif
    return ARGUMENT_ERROR;
  }

  // Calculate sum.
  int sum = registry.load(rsrc) + offset;

  // Verify sum.
  if (sum < 256 || sum >= 768) {
    #ifndef TEST
    std::cout << COLOR_ERROR << "Sum must be in the range 256 to 768." << std::endl;
    #endif
    return VALUE_ERROR;
  }

  char c = *memory.read(sum);
  ex_mem_new.result = c;
  return SUCCESS;
}

int spam::PipeGPR::li(int imm) {
  // Verify arguments.
  if (imm < MIN_IMMEDIATE || imm > MAX_IMMEDIATE) {
    #ifndef TEST
    std::cout << COLOR_ERROR << "Immediate value must be in the range " << MIN_IMMEDIATE << " to " << MAX_IMMEDIATE << "." << std::endl;
    #endif
    return ARGUMENT_ERROR;
  }

  ex_mem_new.result = imm;
  return SUCCESS;
}

int spam::PipeGPR::subi(int rsrc, int imm) {
  // Verify arguments.
  if (rsrc < 0 || rsrc > 31) {
    #ifndef TEST
    std::cout << COLOR_ERROR << "Source register address must be in the range 0 to 31." << std::endl;
    #endif
    return ARGUMENT_ERROR;
  }

  if (imm < MIN_IMMEDIATE || imm > MAX_IMMEDIATE) {
    #ifndef TEST
    std::cout << COLOR_ERROR << "Immediate value must be in the range " << MIN_IMMEDIATE << " to " << MAX_IMMEDIATE << "." << std::endl;
    #endif
    return ARGUMENT_ERROR;
  }

  // Calculate difference.
  int difference = registry.load(rsrc) - imm;

  // Verify difference.
  if (difference > MAX_IMMEDIATE || difference < MIN_IMMEDIATE) {
    #ifndef TEST
    std::cout << COLOR_ERROR << "Difference cannot exceed " << MAX_IMMEDIATE << "." << std::endl;
    #endif
    return VALUE_ERROR;
  }

  ex_mem_new.result = difference;
  return SUCCESS;
}

int spam::PipeGPR::syscall() {
  int op = registry.load(V0_ADDR);
  std::cout << "\tsyscall, op: " << op << " (CIN: " << SYSCALL_CIN << ", COUT: " << SYSCALL_COUT << ")" << std::endl;
  switch (op) {
    case SYSCALL_CIN:
      {
        std::string input;
        #ifndef TEST
        std::cout << "Enter a string to test for palindromicity: ";
        std::cin >> input;
        #endif
        #ifdef TEST
        input = "4\n";
        registry.store(A0_ADDR, 256);
        memory.store(256, (char*)"x: 99");
        #endif

        input += '\0';
        memory.store(registry.load(A0_ADDR), (char*)input.c_str());
      }
      break;
    case SYSCALL_COUT:
      {
        std::string s = "";
        std::cout << "Syscall/cout directive. A0_ADDR: " << A0_ADDR;
        std::cout << ", A0 contents: " << registry.load(A0_ADDR) << std::endl;
        int i = registry.load(A0_ADDR);
        char c = *memory.read(i);

        while(c != '\0' && c != '\n') {
            s += c;
            i++;
            c = *memory.read(i);
        }
        #ifndef TEST
        if(s.find(": ") != std::string::npos) s = s.substr(s.find(": ") + 2);
        std::cout << s << std::endl;
        #endif
        std::cout << "memory @ " << registry.load(A0_ADDR) << ": " << s << std::endl;
        break;
      }
      break;
    case SYSCALL_END:
      end();
      break;
    default:
      return FAIL;
  }
  return op;
}

int spam::PipeGPR::nop() {
  
  return SUCCESS;
}

int spam::PipeGPR::end() {
  pc = -1;
  return SUCCESS;
}


int spam::PipeGPR::fetch() {

  cycles++;

  std::string instruction = std::string(memory.readInstruction(pc));
  if_id_old.instruction = if_id_new.instruction;
  if_id_new.instruction = instruction;

  std::cout << instruction << std::endl;

  if(if_id_new.instruction != instruction) return VALUE_ERROR;

  return SUCCESS;
}

int spam::PipeGPR::decode() {

  std::string instruction = std::string(if_id_old.instruction);
  std::string old = std::string(id_ex_new.instruction);

  id_ex_old.rs = id_ex_new.rs;
  id_ex_old.rt = id_ex_new.rt;
  id_ex_old.pc = id_ex_new.pc;
  id_ex_old.instruction = (char*)old.c_str();
  id_ex_new.instruction = (char*)instruction.c_str();
  id_ex_new.pc = -1;

  std::cout << instruction << std::endl;

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
    instruction = instruction.substr(0, instruction.find(", "));
    std::cout << "\tSource register address: " << instruction << std::endl; 
    int address = atoi(instruction.c_str());
    std::cout << "\tSource register address converted to an integer: " << address << std::endl;
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
    nops++;
    if(id_ex_old.pc >= 0) pc = id_ex_old.pc;
  }
  else if (instruction.find("la") != std::string::npos) {
    int address = atoi(instruction.substr(instruction.find(", ") + 1).c_str());
    id_ex_new.rs = address;
  }
  else return FAIL;


  return SUCCESS;
}

int spam::PipeGPR::execute() {
  ex_mem_old.result = ex_mem_new.result;
  ex_mem_old.instruction = ex_mem_new.instruction;
  ex_mem_new.instruction = id_ex_old.instruction;

  // Get MIPS instruction from ex_mem_new.instruction
  std::string instruction = trim(tolower(ex_mem_new.instruction));
  std::cout << instruction << std::endl;

  // Extract MIPS command from MIPS instruction
  std::string command = "";
  if (instruction.find(" ") != std::string::npos) {
    command = instruction.substr(0, instruction.find(" ")).c_str();
  } else command = instruction;

  /* Data hazard handling */

  // MEM hazard checking
  // TODO: fill this in

  // EXE hazard checking
  // TODO: fill this in

  // Match MIPS command with spam::PipeGPR command
  if (command.compare("add") == 0) {
    add(id_ex_old.rs, id_ex_old.rt);
  } else if (command.compare("addi") == 0) {
    addi(id_ex_old.rs, id_ex_old.rt);
  } else if (command.compare("la") == 0
          || command.compare("lb") == 0){
    // Do nothing; load operations happen in the MEM stage.
  } else if (command.compare("li") == 0) {
    li(id_ex_old.rs);
  } else if (command.compare("subi") == 0) {
    subi(id_ex_old.rs, id_ex_old.rt);
  } else if (command.compare("syscall") == 0) {
    syscall();
  } else if (command.compare("nop") == 0) {
    nop();
  } else if (command.compare("end") == 0) {
    end();
  } else { };

  instructions_executed++;
  // All commands have executed
  return SUCCESS;
}

int spam::PipeGPR::access_memory() {

  mem_wb_old.result = mem_wb_new.result;
  mem_wb_old.instruction = mem_wb_new.instruction;

  mem_wb_new.instruction = ex_mem_old.instruction;

  std::string instruction = mem_wb_new.instruction;
  std::cout << instruction << std::endl;

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
      mem_wb_new.result = address;
    }
    else if(instruction.find("lb") != std::string::npos) {
      std::string grepper = instruction.substr(instruction.find(", ") + 2);
      int reg = atoi(grepper.substr(0, grepper.find(",")).c_str());
      reg = registry.load(reg);

      grepper = grepper.substr(grepper.find(", ") + 2);
      int offset = atoi(grepper.c_str());

      int result = lb(reg, offset);
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
    mem_wb_new.result = ex_mem_old.result;
  }

  else if(instruction.find("syscall") != std::string::npos) {
    memory.store(registry.load(A0_ADDR), (char*)ex_mem_old.input.c_str());
  }

  return SUCCESS;
}

int spam::PipeGPR::cache() {

  std::string instruction = mem_wb_old.instruction;
  std::cout << instruction << std::endl;

  if(instruction.find("add") != std::string::npos
  || instruction.find("addi") != std::string::npos
  || instruction.find("subi") != std::string::npos
  || instruction.find("la") != std::string::npos
  || instruction.find("lb") != std::string::npos
  || instruction.find("li") != std::string::npos) {

    std::cout << "\tOriginal instruction: " << instruction << std::endl;
    instruction = instruction.substr(instruction.find(' ') + 1);
    std::cout << "\tAfter substr: " << instruction << std::endl;
    int reg = atoi(instruction.substr(0, instruction.find(", ")).c_str());
    std::cout << "\tRegister: " << reg << std::endl;
    registry.store(reg, mem_wb_old.result);
    std::cout << "\tStored " << registry.load(reg) << " in register " << reg << "." << std::endl;

  }

  return SUCCESS;
}

int spam::PipeGPR::run() {

  pc = T_BASE_ADDR;
  while(pc >= T_BASE_ADDR){
    std::cout << "CYCLE START =====" << std::endl;

    std::cout << "Fetching ";
    fetch();
    std::cout << "Decoding ";
    decode();
    std::cout << "Executing ";
    execute();
    std::cout << "Accessing memory for instruction ";
    access_memory();
    std::cout << "Caching for instruction ";
    cache();

    std::cout << "CYCLE END   =====" << std::endl << std::endl;
    pc++;
    if(pc >= T_BASE_ADDR + 50) pc = -1;
  }

  std::cout << "RESULTS:" << std::endl;
  std::cout << "\t" << "Total clock cycles: " << cycles << std::endl;
  std::cout << "\t" << "Total instructions executed: " << instructions_executed << std::endl;
  std::cout << "\t" << "NOP count: " << nops << std::endl;

  return SUCCESS;
}
