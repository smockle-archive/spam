#include "gpr.hpp"

// I consulted the following resources for help:
// http://www.cplusplus.com/doc/tutorial/control/

spam::GPR::GPR() {
  pc = 0;
};

spam::GPR::GPR(Registry * rp, Memory * mp) {
  pc = 0;
  registry = *rp;
  memory = *mp;
};

int spam::GPR::addi(int rdest, int rsrc, int imm) {
  // Verify arguments.
  if (rdest < 0 || rdest > 31) {
    #ifndef TEST
    std::cout << COLOR_ERROR << "Destination register address must be in the range 0 to 31." << std::endl;
    #endif
    return ARGUMENT_ERROR;
  }

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

  registry.store(rdest, sum);
  return SUCCESS;
}

int spam::GPR::b(int label_addr) {
  // Verify arguments.
  if (label_addr < 512 || label_addr >= 768) {
    #ifndef TEST
    std::cout << COLOR_ERROR << "Label address must be in the range 512 to 768." << std::endl;
    #endif
    return ARGUMENT_ERROR;
  }

  pc = label_addr;
  return SUCCESS;
}

int spam::GPR::beqz(int rsrc, int label_addr) {
  // Verify arguments.
  if (rsrc < 0 || rsrc > 31) {
    #ifndef TEST
    std::cout << COLOR_ERROR << "Source register address must be in the range 0 to 31." << std::endl;
    #endif
    return ARGUMENT_ERROR;
  }

  if (label_addr < 512 || label_addr >= 768) {
    #ifndef TEST
    std::cout << COLOR_ERROR << "Label address must be in the range 512 to 768." << std::endl;
    #endif
    return ARGUMENT_ERROR;
  }

  // Branch if zero.
  if (registry.load(rsrc) == 0) {
    pc = label_addr;
  }

  return SUCCESS;
}

int spam::GPR::bge(int rsrc1, int rsrc2, int label_addr) {
  // Warn on identical addresses.
  if (rsrc1 == rsrc2) {
    std::cout << COLOR_WARNING << "Destination and source register addresses are identical. It's more common to compare two different registers." << std::endl;
  }

  // Verify arguments.
  if (rsrc1 < 0 || rsrc1 > 31) {
    #ifndef TEST
    std::cout << COLOR_ERROR << "Destination register address must be in the range 0 to 31." << std::endl;
    #endif
    return ARGUMENT_ERROR;
  }

  if (rsrc2 < 0 || rsrc2 > 31) {
    #ifndef TEST
    std::cout << COLOR_ERROR << "Source register address must be in the range 0 to 31." << std::endl;
    #endif
    return ARGUMENT_ERROR;
  }

  if (label_addr < 512 || label_addr >= 768) {
    #ifndef TEST
    std::cout << COLOR_ERROR << "Label address must be in the range 512 to 768." << std::endl;
    #endif
    return ARGUMENT_ERROR;
  }

  // Branch if greater than or equal to.
  if (registry.load(rsrc1) >= registry.load(rsrc2)) {
    pc = label_addr;
  }

  return SUCCESS;
}

int spam::GPR::bne(int rsrc1, int rsrc2, int label_addr) {
  // Warn on identical addresses.
  if (rsrc1 == rsrc2) {
    std::cout << COLOR_WARNING << "Destination and source register addresses are identical. It's more common to compare two different registers." << std::endl;
  }

  // Verify arguments.
  if (rsrc1 < 0 || rsrc1 > 31) {
    #ifndef TEST
    std::cout << COLOR_ERROR << "Destination register address must be in the range 0 to 31." << std::endl;
    #endif
    return ARGUMENT_ERROR;
  }

  if (rsrc2 < 0 || rsrc2 > 31) {
    #ifndef TEST
    std::cout << COLOR_ERROR << "Source register address must be in the range 0 to 31." << std::endl;
    #endif
    return ARGUMENT_ERROR;
  }

  if (label_addr < 512 || label_addr >= 768) {
    #ifndef TEST
    std::cout << COLOR_ERROR << "Label address must be in the range 512 to 768." << std::endl;
    #endif
    return ARGUMENT_ERROR;
  }

  // Branch if not equal to.
  if (registry.load(rsrc1) != registry.load(rsrc2)) {
    pc = label_addr;
  }

  return SUCCESS;
}

int spam::GPR::la(int rdest, int variable_addr) {
  // Verify arguments.
  if (rdest < 0 || rdest > 31) {
    #ifndef TEST
    std::cout << COLOR_ERROR << "Destination register address must be in the range 0 to 31." << std::endl;
    #endif
    return ARGUMENT_ERROR;
  }

  if (variable_addr < 256 || variable_addr >= 512) {
    #ifndef TEST
    std::cout << COLOR_ERROR << "Variable address must be in the range 256 to 512." << std::endl;
    #endif
    return ARGUMENT_ERROR;
  }

  registry.store(rdest, variable_addr);
  return SUCCESS;
}

int spam::GPR::lb(int rdest, int offset, int rsrc) {
  // Warn on identical addresses.
  if (rdest == rsrc) {
    std::cout << COLOR_WARNING << "Destination and source register addresses are identical. It's more common to compare two different registers." << std::endl;
  }

  // Verify arguments.
  if (rdest < 0 || rdest > 31) {
    #ifndef TEST
    std::cout << COLOR_ERROR << "Destination register address must be in the range 0 to 31." << std::endl;
    #endif
    return ARGUMENT_ERROR;
  }

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

  registry.store(rdest, c);
  return SUCCESS;
}

int spam::GPR::li(int rdest, int imm) {
  // Verify arguments.
  if (rdest < 0 || rdest > 31) {
    #ifndef TEST
    std::cout << COLOR_ERROR << "Destination register address must be in the range 0 to 31." << std::endl;
    #endif
    return ARGUMENT_ERROR;
  }

  if (imm < MIN_IMMEDIATE || imm > MAX_IMMEDIATE) {
    #ifndef TEST
    std::cout << COLOR_ERROR << "Immediate value must be in the range " << MIN_IMMEDIATE << " to " << MAX_IMMEDIATE << "." << std::endl;
    #endif
    return ARGUMENT_ERROR;
  }

  registry.store(rdest, imm);

  return SUCCESS;
}

int spam::GPR::subi(int rdest, int rsrc, int imm) {
  // Verify arguments.
  if (rdest < 0 || rdest > 31) {
    #ifndef TEST
    std::cout << COLOR_ERROR << "Destination register address must be in the range 0 to 31." << std::endl;
    #endif
    return ARGUMENT_ERROR;
  }

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

  registry.store(rdest, difference);
  return SUCCESS;
}

int spam::GPR::syscall() {
  int op = registry.load(V0_ADDR);
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

int spam::GPR::run() {
  // Process Memory.t (commands)
  std::string command = "";
  std::string argument = "";
  std::vector<std::string> arguments;

  int ic = 0;
  int cycles = 0;

  pc = T_BASE_ADDR;
  while (pc >= T_BASE_ADDR) {
    // Get MIPS command string from Memory.t at position pc.
    command = trim(tolower(memory.read(pc)));

    // Split MIPS command string into MIPS command and MIPS argument.
    if (command.find(" ") != std::string::npos) {
      argument = trim(command.substr(command.find(" ")).c_str());
      command = command.substr(0, command.find(" ")).c_str();
    }

    // Split MIPS string of one or more spam::GPR arguments (as ints)
    split(argument, ',', arguments);

    // Used to check if pc has changed.
    int pc_clone = pc;


    // Match MIPS command with spam::GPR command
    if (command.compare("addi") == 0) {
      addi(atoi(arguments[0].c_str()), atoi(arguments[1].c_str()), atoi(arguments[2].c_str()));
      cycles += 6;
    } else if (command.compare("b") == 0) {
      b(atoi(arguments[0].c_str()));
      cycles += 4;
    } else if (command.compare("beqz") == 0) {
      beqz(atoi(arguments[0].c_str()), atoi(arguments[1].c_str()));
      cycles += 5;
    } else if (command.compare("bge") == 0) {
      bge(atoi(arguments[0].c_str()), atoi(arguments[1].c_str()), atoi(arguments[2].c_str()));
      cycles += 5;
    } else if (command.compare("bne") == 0) {
      bne(atoi(arguments[0].c_str()), atoi(arguments[1].c_str()), atoi(arguments[2].c_str()));
      cycles += 5;
    } else if (command.compare("la") == 0) {
      la(atoi(arguments[0].c_str()), atoi(arguments[1].c_str()));
      cycles += 5;
    } else if (command.compare("lb") == 0) {
      lb(atoi(arguments[0].c_str()), atoi(arguments[1].c_str()), atoi(arguments[2].c_str()));
      cycles += 6;
    } else if (command.compare("li") == 0) {
      li(atoi(arguments[0].c_str()), atoi(arguments[1].c_str()));
      cycles += 3;
    } else if (command.compare("subi") == 0) {
      subi(atoi(arguments[0].c_str()), atoi(arguments[1].c_str()), atoi(arguments[2].c_str()));
      cycles += 6;
    } else if (command.compare("syscall") == 0) {
      syscall();
      cycles += 8;
    } else if (command.compare("end") == 0) {
      end();
    } else { };

    ic++;
    // Prepare for next command
    command = "";
    argument = "";
    arguments.clear();
    // If we didn't successfully branch, increment.
    if(pc_clone == pc) pc++;
  }
  #ifndef TEST
  std::cout << "RESULTS: " << std::endl;
  std::cout << "\t" << "Instructions run (IC): " << ic << std::endl;
  std::cout << "\t" << "Clock cycles taken (C): " << cycles << std::endl;
  std::cout << "\t" << "Speedup (8 * IC / C): " << (8 * (float)ic / (float)cycles) << std::endl;
  #endif
  // All commands have executed
  return SUCCESS;
}

int spam::GPR::end() {
  pc = -1;
  return SUCCESS;
}
