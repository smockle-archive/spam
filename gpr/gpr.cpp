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
  registry.store(rdest, *memory.read(variable_addr));
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

  registry.store(rdest, *memory.read(sum));
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
  std::cout << "Syscall opcode: " << op << std::endl;
  switch (op) {
    case SYSCALL_CIN:
      {
        std::cout << "SYSCALL_CIN" << std::endl;
        std::string input;
        std::cin >> input;
        memory.store(registry.load(A0_ADDR), (char*)input.c_str());
      }
      break;
    case SYSCALL_COUT:
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
   
  return FAIL;
}

int spam::GPR::end() {
  pc = -1;
  return SUCCESS;
}
